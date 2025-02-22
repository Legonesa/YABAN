
/*		Bu takımımız tarafından geliştirilen bir A3C kütüphanesidir.
			 Bu kütüphane YABAN Projesi için geliştirilmiştir.			*/

#include "A3C.hpp"
// Rastgele değer oluşturma araçları
std::random_device randomDevice;
std::default_random_engine randomEngine(randomDevice());
// Eylem Seç
action_t A3C::selectAction(std::shared_ptr<Environment> environment, float epsilon, const std::vector<float>& policy){
    const bool should_explore = std::uniform_real_distribution<float>(0.0f, 1.0f)(randomEngine) < epsilon;
    if (should_explore) 
        return environment->sample(); //Rastgele bir eylem gerçekleştir.
    else 
        return std::discrete_distribution<action_t>(policy.cbegin(), policy.cend())(randomEngine); //Politiya göre bir eylem gerçekleştir.
}
// Sonraki adımı hesapla.
training_experience_t A3C::extractExperience(memory_t& memory, float nextStateValue){
    assert(!memory.empty());
    const auto n = std::min<uint32_t>(stepReturn, memory.size());
    // Anlık getiriyi kaydet.
    uint32_t t = 0;
    const auto currentState = std::get<0>(memory[t]);
    const auto action = std::get<1>(memory[t]);
    // N'inci adımın getirisini hesapla.
    float nStepReturn = 0.0f;
    for (; t < n; ++t) {
        const auto reward = std::get<2>(memory[t]);
        nStepReturn += std::pow(Gamma, t)*reward;
    }
    const auto done = std::get<4>(memory[n-1]);
    if (!done) { nStepReturn += std::pow(Gamma, n)*nextStateValue; }
    memory.pop_front();
    return training_experience_t{currentState, action, nStepReturn};
}
// Ajanlar
void A3C::agent(uint32_t id, std::shared_ptr<Environment> environment){
    for (uint32_t episode = 1; true; ++episode) {
        const float t = (float)trainingExperienceCount / (maxTrainingExperiences-1);
        const float epsilon = (1-t)*epsilonStart + t*epsilonEnd;
        // Ortamı sıfırla ve yeni döngüye başla.
        observation_t currentState, nextState;
        currentState = environment->reset();
        memory_t memory;
        float reward = 0.0f;
        float episodeReward = 0.0f;
        bool done = false;
        while (!done) {
            // Limite ulaştığında dur.
            if (trainingExperienceCount >= maxTrainingExperiences)
                return;
            // Politika ve value'yu kullan.
            std::vector<float> policy;
            float value;
            std::tie(policy, value) = sharedModel->predictPolicyValue(currentState);
            // Bir eylem seç ve uygula.
            const auto action = selectAction(environment, epsilon, policy);
            std::tie(nextState, reward, done) = environment->step(action);
            episodeReward += reward;
            experience_t experience = experience_t{currentState, action, reward, nextState, done};
            memory.push_back(experience);
            // Simülasyonu eğitim deneyimlerine kaydet.
            while ((memory.size() >= stepReturn) || (done != memory.empty())) {
                const auto training_experience = extractExperience(memory, value);
                trainingExperienceQueue.addValue(training_experience);
            }
            currentState = nextState;
        }

        if (episode % 10 == 0)
            std::cout << "Episode: " << episode << " Reward: " << reward << std::endl;
    }
}
// Değerleri Kaydet
void A3C::fit(const std::vector<training_experience_t>& batch){
    std::vector<observation_t> states;
    std::vector<action_t> actions;
    std::vector<float> rewards;
    observation_t state;
    action_t action;
    float reward;
    for (const auto& experience: batch) {
        std::tie(state, action, reward) = experience;
        states.push_back(state);
        actions.push_back(action);
        rewards.push_back(reward);
    }
    sharedModel->fit(states, actions, rewards);
}
void A3C::trainer(){
    while (trainingExperienceCount < maxTrainingExperiences) {
        const auto batch_size = std::min(BatchSize, maxTrainingExperiences-trainingExperienceCount);
        auto batch = std::vector<training_experience_t>(batch_size);
        for (uint32_t i = 0; i < batch.size(); ++i)
            batch[i] = trainingExperienceQueue.pop_Back();
        fit(batch);
        trainingExperienceCount += batch_size;
    }
}
// Eğitim
void A3C::learn(std::shared_ptr<Model> model, const std::vector<std::shared_ptr<Environment>>& environments){
    // Hata kontrolleri
    assert(BatchSize >= 0);
    assert(stepReturn >= 1);
    assert(Gamma >= 0.0f && Gamma <= 1.0f);
    assert(epsilonStart >= 0.0f && epsilonStart <= 1.0f);
    assert(epsilonEnd   >= 0.0f && epsilonEnd   <= 1.0f && epsilonEnd <= epsilonStart);
    assert(agentCount >= 0);
    assert(maxTrainingExperiences >= 0);
    sharedModel = model;
    assert(environments.size() == agentCount);
    // Ajanları ve eğitimi başlat.
    auto trainer_thread = std::thread(trainer);
    auto agents_threads = std::vector<std::thread>(agentCount);
    for (uint32_t id = 0; id < agentCount; ++id) {
        agents_threads[id] = std::thread(agent, id, environments[id]);
    }
    // Ajanların sonlanmasını bekle.
    for (uint32_t id = 0; id < agentCount; ++id) {
        agents_threads[id].join();
    }
    trainer_thread.join();
    assert(trainingExperienceCount == maxTrainingExperiences);
}

//Parametreleri değiştir.
void A3C::setBatchSize(uint32_t value){
    this->BatchSize = value;
}
void A3C::setGamma(float value){
    this->Gamma = value;
}
void A3C::setEpsilon(float start,float end){
    this->epsilonStart = start;
    this ->epsilonEnd = end;
}
void A3C::setStepReturn(uint32_t value){
    this->stepReturn = value;
}