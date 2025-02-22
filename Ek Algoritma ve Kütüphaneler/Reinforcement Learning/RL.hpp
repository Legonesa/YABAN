
/*      Bu takımımız tarafından geliştirilen bir RL kütüphanesidir.      
             Bu kütüphane YABAN Projesi için geliştirilmiştir.          */

#ifndef RL_HPP
#define RL_HPP

#include "Matrix.hpp"
#include <vector>

class RL{
private:
	Matrix X, H, Y, Y2;
	Matrix Weight0, Weight1, Bias0, Bias1, derrWeight0, derrWeight1, derrBias0, derrBias1;
	long double learningRate;
	long double (*stepFunc)(long double);
	void getMax(const Matrix &matrix, int *y, int *x, long double *output) const; // En yüksek değeri verir.
	std::vector<long double> toCategory(int n, int max) const; // Kategorize eder.
	Matrix feedForward(std::vector<long double> input); // Feed Forward (İleri yayılım.)
public:
	RL(int inputNeuron, int hiddenNeuron, int outputNeuron, long double (*stepFunc)(long double), long double learningRate); // Temeli kur ve değerleri kaydet.
	void learn(std::vector<long double> expected); // Eğitim
};

#endif
