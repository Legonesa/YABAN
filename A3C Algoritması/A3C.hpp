
/*		Bu takımımız tarafından geliştirilen bir A3C kütüphanesidir.
			 Bu kütüphane YABAN Projesi için geliştirilmiştir.			*/

#ifndef A3C_HPP
#define A3C_HPP

#include "Environment.hpp"
#include "Model.hpp"
#include "Queue.hpp"
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <cmath>
#include <random>
#include <deque>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using experience_t = std::tuple<observation_t, action_t, float, observation_t, bool>;
using training_experience_t = std::tuple<observation_t, action_t, float>;
using memory_t = std::deque<experience_t>;

extern uint32_t agentCount;
extern uint32_t maxTrainingExperiences;

class A3C{
private:
	uint32_t BatchSize = 32;
	uint32_t stepReturn = 8;
	float Gamma = 0.99f;
	float epsilonStart = 1.0f;
	float epsilonEnd = 0.15f;
	std::shared_ptr<Model> sharedModel;
	Queue<training_experience_t> trainingExperienceQueue;
	uint32_t trainingExperienceCount = 0;
public:
	action_t selectAction(std::shared_ptr<Environment> environment, float epsilon, const std::vector<float>& policy);// Eylem Seç
	training_experience_t extractExperience(memory_t& memory, float nextStateValue);// Sonraki adımı hesapla.
	void agent(uint32_t Id, std::shared_ptr<Environment> environment);// Ajanlar
	void fit(const std::vector<training_experience_t>& batch);// Değerleri Kaydet
	void trainer();
	void learn(std::shared_ptr<Model> model, const std::vector<std::shared_ptr<Environment>>& environments);// Eğitim
	//Parametreleri değiştir.
	void setBatchSize(uint32_t value);
	void setGamma(float value);
	void setEpsilon(float start, float end);
	void setStepReturn(uint32_t value);
};

#endif // !A3C_HPP