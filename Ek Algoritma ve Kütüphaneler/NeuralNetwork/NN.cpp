
/*          Bu takımımız tarafından geliştirilen bir NN kütüphanesidir.
                Bu kütüphane YABAN Projesi için geliştirilmiştir.
             (Bu versionda Matrix kütüphanesi entegre edilmemiştir.)
    (Matrix kütüphanesinin entegre edildiği versiyon geliştirme aşamasındadır.!)       */

#include <iostream>
#include "NN.hpp"
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>

// Ağın temelini kurar.
NN::NN(int* NNMap, int lenghtofNNMap, int* connectionsMap, int connectionsMapLenght) {
    layerMap = new int[lenghtofNNMap];
    lenghtofNN = lenghtofNNMap;
    connectionMap = new int[connectionsMapLenght + ((connectionsMapLenght / 3) * 2)];
    // Değişkenleri oluşturur ve değer atar.
    CopyArray(layerMap, NNMap, lenghtofNNMap);
    weights = new long double** [lenghtofNNMap - 1];
    for (int i = 0; i < lenghtofNNMap - 1; i++) {
        weights[i] = new long double* [layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++) {
            weights[i][j] = new long double[layerMap[1 + i]];
        }
    }
    dWeights = new long double** [lenghtofNNMap - 1];
    for (int i = 0; i < lenghtofNNMap - 1; i++) {
        dWeights[i] = new long double* [layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++) {
            dWeights[i][j] = new long double[layerMap[i + 1]];
            for (int k = 0; k < layerMap[i + 1]; k++) {
                dWeights[i][j][k] = 0;
            }
        }
    }
    neurons = new long double* [lenghtofNNMap];
    for (int i = 0; i < lenghtofNNMap; i++) {
        neurons[i] = new long double[layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++) {
            neurons[i][j] = 0;
        }
    }
    dNeurons = new long double* [lenghtofNNMap];
    for (int i = 0; i < lenghtofNNMap; i++) {
        dNeurons[i] = new long double[layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++) {
            dNeurons[i][j] = 0;
        }
    }
    eNeurons = new long double* [lenghtofNNMap];
    for (int i = 0; i < lenghtofNNMap; i++) {
        eNeurons[i] = new long double[layerMap[i]];
        for (int j = 0; j < layerMap[i]; j++) {
            eNeurons[i][j] = 0;
        }
    }
    wBias = new long double* [lenghtofNNMap - 1];
    for (int i = 0; i < lenghtofNNMap - 1; i++) {
        wBias[i] = new long double[layerMap[i + 1]];
        for (int j = 0; j < layerMap[i + 1]; j++) {
            wBias[i][j] = 0;
        }
    }
    dwBias = new long double* [lenghtofNNMap - 1];
    for (int i = 0; i < lenghtofNNMap - 1; i++) {
        dwBias[i] = new long double[layerMap[i + 1]];
        for (int j = 0; j < layerMap[i + 1]; j++) {
            dwBias[i][j] = 0;
        }
    }
    // Bağlantı haritasını düzenler ve ağırlıklara rastgele değerler atar.
    int a = 0;
    for (int i = 0; i < connectionsMapLenght; i += 3) {
        int locationofnode, locationofnode0;
        int tmp = 0;
        int layerposition = 0;
        for (int j = 0; j < lenghtofNNMap; j++) {
            tmp += layerMap[j];
            if (tmp >= connectionsMap[i]) {
                locationofnode = (connectionsMap[i] - (tmp - layerMap[j])) - 1;
                locationofnode0 = (connectionsMap[i + 1] - (tmp - layerMap[j])) - 1;
                break;
            }
            else { layerposition++; }
        }
        connectionMap[a] = layerposition;
        connectionMap[a + 1] = locationofnode;
        connectionMap[a + 2] = locationofnode0;

        int locationofnode1;
        tmp = 0;
        layerposition = 0;
        for (int j = 0; j < lenghtofNNMap; j++) {
            tmp += layerMap[j];
            if (tmp >= connectionsMap[i + 2]) {
                locationofnode1 = (connectionsMap[i + 2] - (tmp - layerMap[j])) - 1;
                break;
            }
            else { layerposition++; }
        }
        connectionMap[a + 3] = layerposition;
        connectionMap[a + 4] = locationofnode1;
        a += 5;
    }
    lenghtofConnections = connectionsMapLenght + (connectionsMapLenght / 3) * 2;
    for (int i = 0; i < lenghtofConnections; i += 5) {
        wBias[connectionMap[i + 3] - 1][connectionMap[i + 4]] = GetRandValue(-2.0, 2.0) * (long double)sqrt(2 / layerMap[connectionMap[i]]);
        for (int j = connectionMap[i + 1]; j <= connectionMap[i + 2]; j++) {
            weights[connectionMap[i]][j][connectionMap[i + 4]] = GetRandValue(-2.0, 2.0) * (long double)sqrt(2 / layerMap[connectionMap[i]]);
        }
    }
}
// Eğitim
void NN::Learn(long double** Input, int dataLenght, long double** Output, int epoch) {
    // Girdileri kaydeder.
    input = new long double* [dataLenght];
    for (int i = 0; i < dataLenght; i++) {
        input[i] = new long double[layerMap[0]];
        for (int j = 0; j < layerMap[0]; j++) {
            input[i][j] = Input[i][j];
        }
    }
    // Gerçek çıktıları kaydeder.
    outputT = new long double* [dataLenght];
    for (int i = 0; i < dataLenght; i++) {
        outputT[i] = new long double[layerMap[lenghtofNN - 1]];
        for (int j = 0; j < layerMap[0]; j++) {
            outputT[i][j] = Output[i][j];
        }
    }
    //Feedforward (İleri yayılım)
    for (int g = 0; g < epoch; g++) {
        for (int i = 0; i < dataLenght; i++) {
            //Nöronları sıfırlar.
            for (int j = 0; j < lenghtofNN; j++) {
                for (int k = 0; k < layerMap[j]; k++) {
                    neurons[j][k] = 0;
                }
            }
            // Girdileri ağa sokar.
            for (int j = 0; j < layerMap[0]; j++) {
                neurons[0][j] = input[i][j];
            }
            // Ağ çalıştırılır ve hesaplamalar yapılır.
            for (int j = 1; j < lenghtofNN; j++) {
                for (int k = 0; k < layerMap[j]; k++) {
                    for (int l = 0; l < lenghtofConnections; l += 5) {
                        if (connectionMap[l + 3] == j && connectionMap[l + 4] == k) {
                            for (int m = connectionMap[l + 1]; m <= connectionMap[l + 2]; m++) {
                                neurons[j][k] += neurons[connectionMap[l]][m] * weights[connectionMap[l]][m][k];
                            }
                        }
                    }
                    neurons[j][k] += wBias[j - 1][k] * 1;
                    neurons[j][k] = act(neurons[j][k]);
                }
            }
            //Backpropagation (Geri yayılım.)
            //Nöronlar için hesaplanan hata değerlerini sıfırlar.
            for (int j = 0; j < lenghtofNN; j++) {
                for (int k = 0; k < layerMap[j]; k++) {
                    eNeurons[j][k] = 0;
                    dNeurons[j][k] = 0;
                }
            }
            //Katmanlar için backPropagation yapar ve ağırlıkları günceller.
            for (int j = lenghtofNN - 1; j > -1; j--) {
                if (j == lenghtofNN - 1) {
                    for (int k = 0; k < layerMap[j]; k++) {
                        eNeurons[j][k] = outputT[i][k] - neurons[j][k];
                        dNeurons[j][k] = eNeurons[j][k] * dAct(neurons[j][k]);
                        dwBias[j - 1][k] = 1 * dNeurons[j][k];
                        wBias[j - 1][k] += dwBias[j - 1][k] * learningRate;
                    }
                }
                else {
                    for (int k = 0; k < layerMap[j]; k++) {
                        for (int l = 0; l < lenghtofConnections; l += 5) {
                            if (connectionMap[l] == j && connectionMap[l + 1] <= k && connectionMap[l + 2] >= k) {
                                eNeurons[j][k] += weights[j][k][connectionMap[l + 4]] * dNeurons[connectionMap[l + 3]][connectionMap[l + 4]];
                                dWeights[j][k][connectionMap[l + 4]] = neurons[j][k] * dNeurons[connectionMap[l + 3]][connectionMap[l + 4]];
                                weights[j][k][connectionMap[l + 4]] += dWeights[j][k][connectionMap[l + 4]] * learningRate;
                            }
                        }
                        dNeurons[j][k] = eNeurons[j][k] * dAct(neurons[j][k]);
                        if (j != 0) {
                            dwBias[j - 1][k] = 1 * dNeurons[j][k];
                            wBias[j - 1][k] += dwBias[j - 1][k] * learningRate;
                        }
                    }
                }
            }
        }
    }
}
// Modeli kullan; eğitilmiş olan ağın kullanılmasını sağlar.
void NN::Predict(long double* Input, long double* Output) {
    // Nöronları sıfırlar.
    for (int i = 0; i < lenghtofNN; i++) {
        for (int j = 0; j < layerMap[i]; j++) {
            neurons[i][j] = 0;
        }
    }
    // Girdileri ağa sokar.
    for (int i = 0; i < layerMap[0]; i++) {
        neurons[0][i] = Input[i];
    }
    // Ağ çalıştırılır.
    for (int j = 1; j < lenghtofNN; j++) {
        for (int k = 0; k < layerMap[j]; k++) {
            for (int l = 0; l < lenghtofConnections; l += 5) {
                if (connectionMap[l + 3] == j && connectionMap[l + 4] == k) {
                    for (int m = connectionMap[l + 1]; m <= connectionMap[l + 2]; m++) {
                        neurons[j][k] += neurons[connectionMap[l]][m] * weights[connectionMap[l]][m][k];
                        std::cout << connectionMap[l] << " - " << m << " - " << k << " : " << weights[connectionMap[l]][m][k] << std::endl;
                    }
                }
            }
            neurons[j][k] += wBias[j - 1][k] * 1;
            std::cout << "Bias : " << j << " - " << k << " : " << wBias[j - 1][k] << std::endl;
            neurons[j][k] = act(neurons[j][k]);
        }
    }
    // Çıktılar kaydedilir.
    for (int i = 0; i < layerMap[lenghtofNN - 1]; i++) {
        *(Output + i) = neurons[lenghtofNN - 1][i];
    }
}
// Dizileri kopyalar.
void NN::CopyArray(int* toThisArray, int* fromThisArray, int arraylenght) {
    for (int i = 0; i < arraylenght; i++) {
        *(toThisArray + i) = *(fromThisArray + i);
    }
}
// Belirlenen aralıkta rastgele bir değer verir.
double NN::GetRandValue(double min, double max) {
    long double f = (long double)rand() / RAND_MAX;
    return min + f * (max - min);
}
// Öğrenim oranının ayarlanabilmesini sağlar.
void NN::SetLearningRate(long double learnRate) {
    learningRate = learnRate;
}
// Aktivasyon fonksiyonunun seçilebilmesini sağlar.
void NN::SetACT(int actIndex) {
    ACT = actIndex;
}

/*                      AKTİVASYON FONKSİYONLARI                                */
long double NN::act(long double i) {
    switch (ACT)
    {
    case 0: //Sigmoid Func
        return 1 / (1 + exp((float)-i));
    case 1:
        return i < 0 ? 0 : (i == 0 ? 0.5 : 1);
    case 2:
        return std::max(i * (long double)leakyReluAlpha, i);
    case 3: //TanH
        return (exp(i) - exp(-i)) / (exp(i) + exp(-i));
    }
}
long double NN::dAct(long double i) {
    switch (ACT)
    {
    case 0: //Sigmoid derivative
        return (1 / (1 + exp((float)-i))) * (1 - (1 / (1 + exp((float)-i))));
    case 1:
        return 0;
    case 2:
        return 1 > 0 ? 1 : (long double)leakyReluAlpha;
    case 3: //TanH
        return 1 - (((exp(i) - exp(-i)) / (exp(i) + exp(-i))) * ((exp(i) - exp(-i)) / (exp(i) + exp(-i))));
    }
}
std::vector<long double> NN::softMax(int outputLenght, long double* Outputs) {
    std::vector<long double> softOut(outputLenght);
    long double sum_exp = 0.0;
    for (int i = 0; i < outputLenght; i++) {
        sum_exp = exp(*(Outputs + i));
    }
    for (int i = 0; i < outputLenght; i++) {
        softOut[i] = exp(*(Outputs + i)) / sum_exp;
    }
    return softOut;
}
std::vector<long double> NN::CrossEntropyLoss(std::vector<long double>& softMaxOutputs, std::vector<long double>& ExpectedValues) {
    std::vector<long double> derivatives(softMaxOutputs.size());
    for (int i = 0; i < softMaxOutputs.size(); i++) {
        derivatives[i] = softMaxOutputs[i] - ExpectedValues[i];
    }
    return derivatives;
}
/////////////////////////////////////////////////////////////////////////////////////////////