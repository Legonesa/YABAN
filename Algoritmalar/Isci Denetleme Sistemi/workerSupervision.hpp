#ifndef WORKER_SUPERVISION_HPP
#define WORKER_SUPERVISION_HPP

#include<vector>
// İşçi denetleyicisi
static std::vector<long double> workerSupervision(std::vector<long double> &L,long double W){
	std::vector<long double> result(L.size());
	long double sum = 0;
	for(int i = 0; i < L.size(); i++)
		sum += pow(L.at(i), W);
	for(int i = 0; i < L.size(); i++)
		result[i] = pow(L.at(i), W) / sum;
	return result;
}

#endif