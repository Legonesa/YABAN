#ifndef SIMULATION_SUPERVISION_HPP
#define SIMULATION_SUPERVISION_HPP

#include <vector>

//Simüle Edilme İhtimalini Hesaplama
static std::vector<long double> simulationPosibility(std::vector<long double> &posibilities,std::vector<long double> &realReward, long double *Weight0, long double *Weight1);
//Tahmin edilen simülasyon değerini kullanmadan hesap yapar.
static long double simulationProbabilitywithOthers(std::vector<long double> &posibilities,std::vector<long double> &realReward,std::vector<long double> &recentsimulationProbability);
//Optimizasyonla ilgili değeri verir.
static long double simulationProbabilities(std::vector<long double> &realReward,std::vector<long double> &recentsimulationProbability);
//Optimizasyonla ilgili değeri verir.
static long double optimizationValue(std::vector<std::vector<long double>> posibilities,std::vector<long double> simulationProbabilities,std::vector<long double> simulationProbabilitiesWithother);
//Verim değerlerinin ağırlıklı ortalamasını verir.
static long double yieldWeightedAvarage(std::vector<long double> oldPosibilities,long double posibility, long double x);
//Kaybı hesaplar.
static long double calculateLoss(long double Vx,long double posibility);
//Loss değerine uygun olarak ağırlıkları günceller ve sinir ağını eğitir.
static void updateWeights(std::vector<long double> &posibilities,std::vector<long double> &realReward,long double *Weight0,long double *Weight1,long double loss, long double learningRate);

#endif