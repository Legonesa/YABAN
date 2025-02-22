
/*		Bu takımımız tafaından geliştirilen bir Matrix kütüphanesidir.
		     Bu kütüphane YABAN Projesi için geliştirilmiştir!			*/

#include "Matrix.hpp"

Matrix::Matrix(){}
// Boş matrix oluşturur.
Matrix::Matrix(int height,int width){
	this->height = height;
	this->width = width;
	this->array = std::vector<std::vector<long double>>(height, std::vector<long double>(width));
}
// Bir vector kullanarak matrix oluşturur.
Matrix::Matrix(std::vector<std::vector<long double>> const &array){
	assert(array.size()!=0);
	this->height = array.size();
	this->width = array[0].size();
	this->array = array;
}
// Matrixi başka bir matrix ile toplar.
Matrix Matrix::add(Matrix const &matrix) const{
	assert(height == matrix.height && width == matrix.width);
	Matrix result(height, width);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++)
			result.array[i][j] = array[i][j] + matrix.array[i][j];
	}
	return result;
}
// Matricten başka bir matrixi çıkarır.
Matrix Matrix::subtract(Matrix const &matrix) const{
	assert(height == matrix.height && width == matrix.width);
	Matrix result(height, width);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++)
			result.array[i][j] = array[i][j] - matrix.array[i][j];
	}
	return result;
}
// Matrixi başka bir matrix ile çarpar.
Matrix Matrix::multiply(Matrix const &matrix) const{
	assert(height == matrix.height && width == matrix.width);
	Matrix result(height, width);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++)
			result.array[i][j] = array[i][j] * matrix.array[i][j];
	}
	return result;
}
Matrix Matrix::dot(Matrix const &matrix) const{
	assert(width == matrix.height);
	Matrix result(height, width);
	long double f = 0;
	for(int i = 0; i < height; i++){
		for(int l = 0; l < matrix.width; l++){
			for(int j = 0; j < width; j++)
				f += array[i][j] * matrix.array[j][l];
			result.array[i][l] = f;
			f = 0;
		}
	}
	return result;
}
// Matrixte satır ve sütunların yerini değiştirir.
Matrix Matrix::transpose() const{
	Matrix result(width, height);
	for(int i = 0; i < width; i++){
		for(int l = 0; l < height; l++)
			result.array[i][l] = array[l][i];
	}
	return result;
}
// Matrixi bir değer ile çarpar.
Matrix Matrix::multiply(long double const &value) const{
	Matrix result(height, width);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++)
			result.array[i][j] = array[i][j] * value;
	}
	return result;
}
// Matrix elemanlarına bir fonksiyon uygular.
Matrix Matrix::useFunction(long double (*func)(long double)) const{
	Matrix result(height, width);
	for(int i = 0; i < height; i++){
		for(int l = 0; l < width; l++)
			result.array[i][l] = (*func)(array[i][l]);
	}
	return result;
}
// Matrixin sütun sayısını verir.
int Matrix::getWidth() const{
	return width;
}
// Matrixin satır sayısını verir.
int Matrix::getHeight() const{
	return height;
}
// Matrixten bir eleman alır.
long double Matrix::getValue(int row,int column) const{
	assert(row >= 0 && row < height && column >= 0 && column < width);
	return array[row][column];
}
// Matrixteki tüm elemanları toplar.
long double Matrix::sum() const{
	long double sum = 0.0;
	for(int i = 0; i < height; i++){
		for(int l = 0; l < width; l++)
			sum += array[i][l];
	}
	return sum;
}