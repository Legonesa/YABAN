
/*		Bu takımımız tafaından geliştirilen bir Matrix kütüphanesidir.
		     Bu kütüphane YABAN Projesi için geliştirilmiştir!			*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<iostream>
#include<vector>
#include<assert.h>

class Matrix{
private:
	std::vector<std::vector<long double>> array;
	int height, width;
public:
	Matrix();
	Matrix(int height, int width); //Boş matrix oluştur.
	Matrix(std::vector<std::vector<long double>> const &array); //Bir vector kullanarak matrix oluştur.
	Matrix add(Matrix const &matrix) const; // Matrix ile başka bir matrixi toplar.
	Matrix subtract(Matrix const &matrix) const; // Matrixten başka bir matrixi çıkarır.
	Matrix multiply(Matrix const &matrix) const; // Matrixi başka bir matrix ile çarpar.
	Matrix dot(Matrix const &matrix) const;
	Matrix transpose() const; // Matrixte satır ve sütunların yerlerini değiştirir.
	Matrix multiply(long double const &value) const; // Matrixi bir değer ile çarpar.
	Matrix useFunction(long double (*func)(long double)) const; //Matrix elemanlarına bir fonksiyon uygular.
	int getWidth() const; //Matrixin kolon sayısını verir.
	int getHeight() const; //Matrixin satır sayısını verir.
	long double getValue(int row, int column) const; //Matrixten veri alır.
	long double sum() const; //Matrixteki tüm elemanları toplar.
};

#endif // !AEI_MATRIX
