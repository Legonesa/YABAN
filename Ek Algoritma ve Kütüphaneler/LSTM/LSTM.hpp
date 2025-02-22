
/*         Bu takımımız tarafından geliştirilen bir LSTM kütüphanesidir.
                 Bu kütüphane YABAN Projesi için geliştirilmiştir.
              (Bu versionda Matrix kütüphanesi entegre edilmemiştir.)
     (Matrix kütüphanesinin entegre edildiği versiyon geliştirme aşamasındadır.!)       */

#ifndef LSTM_HPP
#define LSTM_HPP
#include <vector>

static enum Device{
    CPU = 0, 
    CUDA
};
class LSTM
{
private:
    Device _device;
    long double LTM = 0, STM = 0;
    std::vector<long double> inputs;
    long double inputWeights[4];
    long double STMWeights[4];
    long double BiaS[4];
    long double Neurons[5];
    long double *d_LR, *d_LTM, *d_STM, *d_Neurons, *d_Loss, *d_OD,
            *d_FGD, *d_IGD, *d_CGD, *d_Input, *d_IW, *d_STMW, *d_BW,
            *d_oldSTM, *d_NSD, *d_NINPUT, *d_oldLTM;
    long double Sigmoid(long double i);
    long double TanH(long double i);
    long double DTanH(long double i);
    double GetRandValue(double min, double max);
    long double MSE(long double Predicted, long double Expected);
public:
    LSTM(const std::vector<long double>& input, Device device);
    void Learn(long double learningRate, int epoch, int threadSize);
    long double Predict(const std::vector<long double>& input);
    //~LSTM();
};
#endif
