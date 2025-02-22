
/*         Bu takımımız tarafından geliştirilen bir NN kütüphanesidir.
                Bu kütüphane YABAN Projesi için geliştirilmiştir.
             (Bu versionda Matrix kütüphanesi entegre edilmemiştir.)
    (Matrix kütüphanesinin entegre edildiği versiyon geliştirme aşamasındadır.!)       */

#ifndef NEURAL_NETWORK_HPP 
#define NEURAL_NETWORK_HPP
#include <vector>

class NN {
private:
    long double** input;
    long double** output;
    long double** outputT;
    long double*** weights;
    long double*** dWeights;
    long double** neurons;
    long double** dNeurons;
    long double** eNeurons;
    long double** wBias;
    long double** dwBias;
    int* connectionMap;
    int* layerMap;
    int ACT = 3;
    int lenghtofNN;
    int lenghtofConnections;
    float leakyReluAlpha = 0.3f;
    long double learningRate = 0.001;
    void CopyArray(int* toThisArray, int* fromThisArray, int arraylenght);
    double GetRandValue(double min, double max);
    long double act(long double i);
    long double dAct(long double i);
    std::vector<long double> softMax(int outputLenght, long double* Outputs);
    std::vector<long double> CrossEntropyLoss(std::vector<long double>& softMaxOutputs, std::vector<long double>& ExpectedValues);
public:
    NN(int* NNMap, int lenghtofNNMap, int* connectionsMap, int connectionsMapLenght); // Ağın temelini kur.
    void Learn(long double** Input, int dataLenght, long double** Output, int epoch); // Eğitim
    void Predict(long double* Input, long double* Output); // Modeli kullan.
    void SetLearningRate(long double learnRate); // Öğrenme değerini ayarla.
    void SetACT(int actIndex); // Aktivasyon fonksiyonunu ayarla.
};

#endif