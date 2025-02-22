
/*          Bu takımımız tarafından geliştirilen bir LSTM kütüphanesidir.
                 Bu kütüphane YABAN Projesi için geliştirilmiştir.
              (Bu versionda Matrix kütüphanesi entegre edilmemiştir.)
     (Matrix kütüphanesinin entegre edildiği versiyon geliştirme aşamasındadır.!)       */

#include "LSTM.hpp"
#include "DL_kernel.hpp"
#include <iostream>
#include <random>

// LSTM modülünü oluştur.
LSTM::LSTM(const std::vector<long double>& input, Device device) {
    inputs = input;
    _device = device;
    // Ağırlıklara rastgele değerler ata.
    for (int i = 0; i < 4; i++) {
        inputWeights[i] = GetRandValue(-0.5, 0.5);
        STMWeights[i] = GetRandValue(-0.5, 0.5);
        BiaS[i] = GetRandValue(-0.5, 0.5);
    }
}
// Eğitim
void LSTM::Learn(long double learningRate, int epoch, int threadSize) {
    // Çalıştıralacak cihazı seç.
    switch(_device){
    case CPU:
        for (int q = 0; q < epoch; q++) {
            long double total_loss = 0;
            LTM = 0; STM = 0;
            std::cout << "Epoch: " << q << std::endl;
            for (int d = 0; d < inputs.size() - 1; d++) {
                long double oldLTM, oldSTM;
                //Feed Forward (ileri yayılım.)
                Neurons[0] = Sigmoid((inputs[d] * inputWeights[0]) + (STM * STMWeights[0]) + BiaS[0]);
                Neurons[1] = Sigmoid((inputs[d] * inputWeights[1]) + (STM * STMWeights[1]) + BiaS[1]);
                Neurons[2] = TanH((inputs[d] * inputWeights[2]) + (STM * STMWeights[2]) + BiaS[2]);
                Neurons[3] = Sigmoid((inputs[d] * inputWeights[3]) + (STM * STMWeights[3]) + BiaS[3]);
                oldLTM = LTM;
                LTM *= Neurons[0];
                LTM += Neurons[1] * Neurons[2];
                Neurons[4] = TanH(LTM);
                oldSTM = STM;
                STM = Neurons[3] * Neurons[4];
                //Back Propagation (Hata değerlerini hesapla ve buna uygun bir şekilde ağırlıkları güncelle.)
                total_loss += MSE(STM, inputs[d + 1]);
                long double dLoss = STM - inputs[d + 1];
                long double NeuronStateDerivative = dLoss * Neurons[3] * DTanH(LTM);
                long double ForgetGateDerivative = NeuronStateDerivative * oldLTM * Neurons[0] * (1 - Neurons[0]);
                long double inGateDerivative = NeuronStateDerivative * Neurons[2] * Neurons[1] * (1 - Neurons[1]);
                long double CandidateGateDerivative = NeuronStateDerivative * Neurons[1] * (1 - (Neurons[2] * Neurons[2]));
                inputWeights[0] -= ForgetGateDerivative * inputs[d] * learningRate;
                STMWeights[0] -= ForgetGateDerivative * oldSTM * learningRate;
                BiaS[0] -= ForgetGateDerivative * learningRate;
                inputWeights[1] -= inGateDerivative * inputs[d] * learningRate;
                STMWeights[1] -= inGateDerivative * oldSTM * learningRate;
                BiaS[1] -= inGateDerivative * learningRate;
                inputWeights[2] -= CandidateGateDerivative * inputs[d] * learningRate;
                STMWeights[2] -= CandidateGateDerivative * oldSTM * learningRate;
                BiaS[2] -= CandidateGateDerivative * learningRate;
                inputWeights[3] -= CandidateGateDerivative * inputs[d] * learningRate;
                STMWeights[3] -= CandidateGateDerivative * oldSTM * learningRate;
                BiaS[3] -= CandidateGateDerivative * learningRate;
            }
            std::cout << "Total Loss: " << total_loss / (inputs.size() - 1) << std::endl;
        }
        break;
    case CUDA:
        CUDA_LSTM_BEGIN(&inputWeights[0], &STMWeights[0], &BiaS[0],&d_LR,&d_LTM,&d_STM,&d_Neurons,&d_Loss,&d_FGD,&d_IGD,&d_CGD,&d_Input,
            &d_IW, &d_STMW, &d_BW, &d_oldSTM, &d_oldLTM, &d_NSD, &d_NINPUT);
        for(int q = 0; q < epoch; q++){
            CUDA_LSTM_RESET_LTM_STM(d_LTM, d_STM);
            std::cout << "Epoch: " << q << std::endl;
            for(int d = 0; d < inputs.size() -1; d++){
                CUDA_LSTM_FEEDFORWARD(&inputs[d], &inputs[d+1], d_NINPUT,d_Neurons,d_Input,d_STM,d_LTM,d_IW,d_STMW,d_BW,d_oldSTM,d_oldLTM,threadSize); //Feed Forward (İleri yayılım.)
                //Back Propagation (Hata değerlerini hesapla ve buna uygun bir şekilde ağırlıkları güncelle.)
                CUDA_LSTM_BACKPROPAGATION(d_Neurons, d_oldLTM, d_LTM, d_STM, d_Loss, d_NSD, d_FGD, d_IGD, d_CGD, d_IW, d_STMW, d_BW, d_oldSTM, d_LR, d_Input, d_NINPUT, &learningRate, threadSize);
            }
        }
        // Elde edilen son ağırlık değerlerini local rame kaydet.
        CUDA_LSTM_SAVE_LAST_WEIGHTS(&inputWeights[0],d_IW,&STMWeights[0], d_STMW, &BiaS[0], d_BW);
        _DLkernel_Cuda_RESET(); //GPU'nun hafızasını temizle.
        break;
    }
}
// Elde edilen son değerlerle modeli kullan.
long double LSTM::Predict(const std::vector<long double>& input) {
    LTM = 0; STM = 0;
    inputs = input;
    for (int d = 0; d < inputs.size(); d++) {
        Neurons[0] = Sigmoid((inputs[d] * inputWeights[0]) + (STM * STMWeights[0]) + BiaS[0]);
        Neurons[1] = Sigmoid((inputs[d] * inputWeights[1]) + (STM * STMWeights[1]) + BiaS[1]);
        Neurons[2] = TanH((inputs[d] * inputWeights[2]) + (STM * STMWeights[2]) + BiaS[2]);
        Neurons[3] = Sigmoid((inputs[d] * inputWeights[3]) + (STM * STMWeights[3]) + BiaS[3]);
        LTM *= Neurons[0];
        LTM += Neurons[1] * Neurons[2];
        Neurons[4] = TanH(LTM);
        STM = Neurons[3] * Neurons[4];
    }
    return STM;
}

// Aktivasyon fonksiyonları ve türevleri
long double LSTM::Sigmoid(long double i) {
    return 1 / (1 + exp((float)-i));
}
long double LSTM::TanH(long double i) {
    return (exp(i) - exp(-i)) / (exp(i) + exp(-i));
}
long double LSTM::DTanH(long double i) {
    return 1 - (((exp(i) - exp(-i)) / (exp(i) + exp(-i))) * ((exp(i) - exp(-i)) / (exp(i) + exp(-i))));
}
long double LSTM::MSE(long double Predicted, long double Expected) {
    return 0.5 * pow((Expected - Predicted), 2);
}
// Rastgele değer oluştur.
double LSTM::GetRandValue(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}