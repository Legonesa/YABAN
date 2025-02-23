#include "SimulationSupervision.hpp"

//Simüle Edilme İhtimalini Hesaplama
static std::vector<long double> simulationPosibility(std::vector<long double> &posibilities,std::vector<long double> &realReward, long double *Weight0, long double *Weight1){
	std::vector<long double> result(posibilities.size());
	for(int i = 0; i < posibilities.size(); i++)
		result[i] = (posibilities.at(i) * (*Weight0)) + (realReward.at(i) * (*Weight1));
	return result;
}
//Tahmmin edilen simülasyon değerini kullanarak hesap yapar.
static long double simulationProbabilitywithOthers(std::vector<long double> &posibilities,std::vector<long double> &realReward,std::vector<long double> &recentsimulationProbability){
	long double Tsum = 0;
	for(int i = 0; i < realReward.size(); i++){
		Tsum += realReward.at(i) * recentsimulationProbability.at(i) * posibilities.at(i);
	}
	return posibilities.at(0) * realReward.at(0) + Tsum;
}
//Tahmin edilen simülasyon değerini kullanmadan hesap yapar.
static long double simulationProbabilities(std::vector<long double> &realReward,std::vector<long double> &recentsimulationProbability){
	long double Tsum = 0;
	for(int i = 0; i < realReward.size(); i++)
		Tsum += realReward.at(i) * recentsimulationProbability.at(i);
	return realReward.at(0) * recentsimulationProbability.at(0) + Tsum;
}
//Optimizasyonla ilgili değeri verir.
static long double optimizationValue(std::vector<std::vector<long double>> posibilities,std::vector<long double> simulationProbabilities,std::vector<long double> simulationProbabilitiesWithother){
	long double sum1 = 0, sum2 = 0;
	for(int i = 0; i < posibilities.size(); i++)
		sum1 += 1 - posibilities.at(i).at(0);
	for(int i = 0; i < posibilities.size(); i++)
		sum2 += std::abs(simulationProbabilities.at(i) - simulationProbabilitiesWithother.at(i));
	return sum1/sum2;
}
//Verim değerlerinin ağırlıklı ortalamasını verir.
static long double yieldWeightedAvarage(std::vector<long double> oldPosibilities,long double posibility, long double x){
	long double sum0_1 = 0, sum0_2 = 0, sum0_3 = 0;
	for(int i = 0; i < oldPosibilities.size(); i++)
		sum0_1 += pow(oldPosibilities.at(i), x);
	for(int i = 0; i < oldPosibilities.size(); i++)
		sum0_2 += (pow(oldPosibilities.at(i),x) / sum0_1)*oldPosibilities.at(i);
	for(int i = 0; i < oldPosibilities.size(); i++)
		sum0_3 += (pow(oldPosibilities.at(i),x) / sum0_1);
	return sum0_2/sum0_3;
}
//Kaybı hesaplar.
static long double calculateLoss(long double Vx,long double posibility){
	return 0.5 * pow((Vx - posibility), 2);
}
//Loss değerine uygun olarak ağırlıkları günceller ve sinir ağını eğitir.
static void updateWeights(std::vector<long double> &posibilities,std::vector<long double> &realReward,long double *Weight0,long double *Weight1,long double loss, long double learningRate){
	long double derrWeight0 = 0, derrWeight1 = 0;
	for(int i = 0; i < posibilities.size(); i++){
		derrWeight0 += (loss * posibilities.at(i)) / posibilities.size();
		derrWeight1 += (loss * realReward.at(i)) / posibilities.size();
	}
	*Weight0 -= derrWeight0 * learningRate; *Weight1 -= derrWeight1 * learningRate;
}