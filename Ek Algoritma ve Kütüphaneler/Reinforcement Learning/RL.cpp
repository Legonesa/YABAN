
/*      Bu takımımız tarafından geliştirilen bir RL kütüphanesidir.      
             Bu kütüphane YABAN Projesi için geliştirilmiştir.          */

#include "RL.hpp"
#include <random>

// Rastgele bir değer sağlar.
static long double GetRandValue(long double x){
    double min = -2.0; double max = 2.0;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}
// Aktivasyon fonksiyonları
static long double sigmoid(long double x){
    return 1/(1+exp(-x));
}
static long double dSigmoid(long double x){
    return exp(-x)/(pow(1+exp(-x), 2));
}

// Temeli oluşturur ve ağırlıklara rastgele değerler atar.
RL::RL(int inputNeuron,int hiddenNeuron,int outputNeuron, long double (*stepFunc)(long double), long double learningRate){
    this->learningRate = learningRate;
    this->stepFunc = stepFunc;
    Weight0 = Matrix(inputNeuron, hiddenNeuron);
    Weight1 = Matrix(hiddenNeuron, outputNeuron);
    Bias0 = Matrix(1, hiddenNeuron);
    Bias1 = Matrix(1, outputNeuron);
    Weight0 = Weight0.useFunction(GetRandValue);
    Weight1 = Weight1.useFunction(GetRandValue);
    Bias0 = Bias0.useFunction(GetRandValue);
    Bias1 = Bias1.useFunction(GetRandValue);
}
// Feedforward (İleri yayılım)
Matrix RL::feedForward(std::vector<long double> input){
    this->X = Matrix({input});
    this->H = X.dot(Weight0).add(Bias0).useFunction(sigmoid);
    this->Y = H.dot(Weight1).add(Bias1).useFunction(sigmoid);
    return Y;
}
// Eğitim
void RL::learn(std::vector<long double> expected){
    Y2 = Matrix({expected});
    derrBias1 = Y.subtract(Y2).multiply(H.dot(Weight1).add(Weight1).useFunction(dSigmoid));
    derrBias0 = derrBias1.dot(Weight1.transpose()).multiply(X.dot(Weight0).add(Bias0).useFunction(dSigmoid));
    derrWeight1 = H.transpose().dot(derrBias1);
    derrWeight0 = X.transpose().dot(derrBias0);
    // Ağırlıkları günceller.
    Weight0 = Weight0.subtract(derrWeight0.multiply(learningRate));
    Weight1 = Weight1.subtract(derrWeight1.multiply(learningRate));
    Bias0 = Bias0.subtract(derrBias0.multiply(learningRate));
    Bias1 = Bias1.subtract(derrBias1.multiply(learningRate));
}
// En büyük değeri verir.
void RL::getMax(const Matrix &matrix,int *row,int *column,long double *output) const{
    long double max = LDBL_MIN;
    for(int i = 0; i < matrix.getHeight(); i++){
        for(int j = 0; j < matrix.getWidth(); j++){
            if(max < matrix.getValue(i,j)){
                max = matrix.getValue(i, j);
                if(row != NULL) *row = i; if(column != NULL) *column = j;
            }
        }
    }
    if(output != NULL)
        *output = max;
}
// Kategorize eder.
std::vector<long double> RL::toCategory(int n,int max) const{
    std::vector<long double> v(max, 0);
    v[n] = 1; return v;
}
