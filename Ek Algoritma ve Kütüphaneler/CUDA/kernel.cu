#include <iostream>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>
#include "kernel.hpp"

__global__ void CalculateCUDA(int* a, int* b, int dataSize, int calculation){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize){
		switch(calculation){
		case 0:
			a[idx] += b[idx];
			break;
		case 1:
			a[idx] -= b[idx];
			break;
		case 2:
			a[idx] *= b[idx];
			break;
		case 3:
			a[idx] /= b[idx];
			break;
		default:
			a[idx] = 0;
			break;
		}
	}
}
__global__ void CalculateCUDA(double* a, double* b, int dataSize, int calculation){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize){
		switch(calculation){
		case 0:
			a[idx] += b[idx];
			break;
		case 1:
			a[idx] -= b[idx];
			break;
		case 2:
			a[idx] *= b[idx];
			break;
		case 3:
			a[idx] /= b[idx];
			break;
		default:
			a[idx] = 0;
			break;
		}
	}
}
__global__ void CalculateCUDA(long double* a, long double* b, int dataSize, int calculation){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize){
		switch(calculation){
		case 0:
			a[idx] += b[idx];
			break;
		case 1:
			a[idx] -= b[idx];
			break;
		case 2:
			a[idx] *= b[idx];
			break;
		case 3:
			a[idx] /= b[idx];
			break;
		default:
			a[idx] = 0;
			break;
		}
	}
}

__global__ void SigmoidCuda(double* Input){
	Input[0] = 1 / (1+exp((float)-Input[0]));
}
__global__ void SigmoidCuda(long double* Input){
	Input[0] = 1 / (1+exp((float)-Input[0]));
}
__global__ void SigmoidCuda(double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = 1 / (1+exp((float)-Input[idx]));
}
__global__ void SigmoidCuda(long double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = 1 / (1+exp((float)-Input[idx]));
}

__global__ void DSigmoidCuda(double* Input){
	Input[0] = (1 / (1 + exp((float)-Input[0]))) * (1 - (1 / (1 + exp((float)-Input[0]))));
}
__global__ void DSigmoidCuda(long double* Input){
	Input[0] = (1 / (1 + exp((float)-Input[0]))) * (1 - (1 / (1 + exp((float)-Input[0]))));
}
__global__ void DSigmoidCuda(double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = (1 / (1 + exp((float)-Input[idx]))) * (1 - (1 / (1 + exp((float)-Input[idx]))));
}
__global__ void DSigmoidCuda(long double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = (1 / (1 + exp((float)-Input[idx]))) * (1 - (1 / (1 + exp((float)-Input[idx]))));;
}

__global__ void TanHCUDA(double* Input){
	Input[0] = (exp((float)Input[0]) - exp((float)-Input[0])) / (exp((float)Input[0]) + exp((float)-Input[0]));
}
__global__ void TanHCUDA(long double* Input){
	Input[0] = (exp((float)Input[0]) - exp((float)-Input[0])) / (exp((float)Input[0]) + exp((float)-Input[0]));
}
__global__ void TanHCUDA(double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = (exp((float)Input[idx]) - exp((float)-Input[idx])) / (exp((float)Input[idx]) + exp((float)-Input[idx]));
}
__global__ void TanHCUDA(long double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = (exp((float)Input[idx]) - exp((float)-Input[idx])) / (exp((float)Input[idx]) + exp((float)-Input[idx]));
}

__global__ void DTanHCUDA(double* Input){
	Input[0] = 1 - (((exp((float)Input[0]) - exp((float)-Input[0])) / (exp((float)Input[0]) + exp((float)-Input[0]))) * ((exp((float)Input[0]) - exp((float)-Input[0])) / (exp((float)Input[0]) + exp((float)-Input[0]))));
}
__global__ void DTanHCUDA(long double* Input){
	Input[0] = 1 - (((exp((float)Input[0]) - exp((float)-Input[0])) / (exp((float)Input[0]) + exp((float)-Input[0]))) * ((exp((float)Input[0]) - exp((float)-Input[0])) / (exp((float)Input[0]) + exp((float)-Input[0]))));
}
__global__ void DTanHCUDA(double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = 1 - (((exp((float)Input[idx]) - exp((float)-Input[idx])) / (exp((float)Input[idx]) + exp((float)-Input[idx]))) * ((exp((float)Input[idx]) - exp((float)-Input[idx])) / (exp((float)Input[idx]) + exp((float)-Input[idx]))));
}
__global__ void DTanHCUDA(long double* Input, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize)
		Input[idx] = 1 - (((exp((float)Input[idx]) - exp((float)-Input[idx])) / (exp((float)Input[idx]) + exp((float)-Input[idx]))) * ((exp((float)Input[idx]) - exp((float)-Input[idx])) / (exp((float)Input[idx]) + exp((float)-Input[idx]))));
}

__global__ void MSECUDA(double* Predict, double* Except, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize){
		Predict[idx] = 0.5 * pow((Except[idx] - Predict[idx]), 2);
	}
}
__global__ void MSECUDA(long double* Predict, long double* Except, int dataSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < dataSize){
		Predict[idx] = 0.5 * pow((Except[idx] - Predict[idx]), 2);
	}
}

void Calculate_CUDA(int* a, int* b, int* Output, Kernel_Calculation calculation, int dataSize, int threadSize){
	int* d_a, * d_b;
	if (cudaMalloc((void**)&d_a, sizeof(int) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if(cudaMalloc((void**)&d_b, sizeof(int) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		cudaFree(d_a);
		exit(0);
	}
	if (cudaMemcpy(d_a, a, sizeof(int) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess || cudaMemcpy(d_b, b, sizeof(int) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_a); cudaFree(d_b);
		exit(0);
	}
	CalculateCUDA<<<dataSize/threadSize + 1, threadSize>>>(d_a, d_b, dataSize, calculation);
	if (cudaMemcpy(Output, d_a, sizeof(int) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_a); cudaFree(d_b);
		exit(0);
	}
	cudaFree(d_a); cudaFree(d_b);
	cudaDeviceSynchronize();
}
void Calculate_CUDA(double* a, double* b, double* Output, Kernel_Calculation calculation, int dataSize, int threadSize) {
	double* d_a, * d_b;
	if (cudaMalloc((void**)&d_a, sizeof(double) * dataSize) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMalloc((void**)&d_b, sizeof(double) * dataSize) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		cudaFree(d_a);
		exit(0);
	}
	if (cudaMemcpy(d_a, a, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess || cudaMemcpy(d_b, b, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_a); cudaFree(d_b);
		exit(0);
	}
	CalculateCUDA<<<dataSize / threadSize + 1, threadSize>>>(d_a, d_b, dataSize, calculation);
	if (cudaMemcpy(Output, d_a, sizeof(double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_a); cudaFree(d_b);
		exit(0);
	}
	cudaFree(d_a); cudaFree(d_b);
	cudaDeviceSynchronize();
}
void Calculate_CUDA(long double* a, long double* b, long double* Output, Kernel_Calculation calculation, int dataSize, int threadSize) {
	long double *d_a, *d_b;
	if (cudaMalloc((void**)&d_a, sizeof(long double) * dataSize) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMalloc((void**)&d_b, sizeof(long double) * dataSize) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		cudaFree(d_a);
		exit(0);
	}
	if (cudaMemcpy(d_a, a, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess || cudaMemcpy(d_b, b, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_a); cudaFree(d_b);
		exit(0);
	}
	CalculateCUDA <<<dataSize / threadSize + 1, threadSize >>>(d_a, d_b, dataSize, calculation);
	if (cudaMemcpy(Output, d_a, sizeof(long double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_a); cudaFree(d_b);
		exit(0);
	}
	cudaFree(d_a); cudaFree(d_b);
	cudaDeviceSynchronize();
}

double Sigmoid_CUDA(double *Input){
	double *d_Input;
	double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	SigmoidCuda<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
long double Sigmoid_CUDA(long double *Input){
	long double *d_Input;
	long double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(long double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	SigmoidCuda<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(long double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
void Sigmoid_CUDA(long double *Input, long double *Output, int dataSize, int threadSize){
	long double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(long double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	SigmoidCuda <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(long double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}
void Sigmoid_CUDA(double *Input, double *Output, int dataSize, int threadSize){
	double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	SigmoidCuda <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}

double DSigmoid_CUDA(double *Input){
	double *d_Input;
	double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	DSigmoidCuda<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
long double DSigmoid_CUDA(long double *Input){
	long double *d_Input;
	long double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(long double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	DSigmoidCuda<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(long double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
void DSigmoid_CUDA(long double *Input, long double *Output, int dataSize, int threadSize){
	long double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(long double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	DSigmoidCuda <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(long double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}
void DSigmoid_CUDA(double *Input, double *Output, int dataSize, int threadSize){
	double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	DSigmoidCuda <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}

double TanH_CUDA(double *Input){
	double *d_Input;
	double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	TanHCUDA<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
long double TanH_CUDA(long double *Input){
	long double *d_Input;
	long double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(long double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	TanHCUDA<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(long double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
void TanH_CUDA(long double *Input, long double *Output, int dataSize, int threadSize){
	long double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(long double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	TanHCUDA <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(long double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}
void TanH_CUDA(double *Input, double *Output, int dataSize, int threadSize){
	double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	TanHCUDA <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}

double DTanH_CUDA(double *Input){
	double *d_Input;
	double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	DTanHCUDA<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
long double DTanH_CUDA(long double *Input){
	long double *d_Input;
	long double Output;
	if (cudaMalloc((void**)&d_Input, sizeof(long double)) != cudaSuccess) {
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		return 0;
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double), cudaMemcpyHostToDevice) != cudaSuccess) {
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	DTanHCUDA<<<1, 1>>>(d_Input);
	if (cudaMemcpy(&Output, d_Input, sizeof(long double), cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		return 0;
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
	return Output;
}
void DTanH_CUDA(long double *Input, long double *Output, int dataSize, int threadSize){
	long double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(long double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	DTanHCUDA <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(long double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}
void DTanH_CUDA(double *Input, double *Output, int dataSize, int threadSize){
	double *d_Input;
	if (cudaMalloc((void**)&d_Input, sizeof(double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if (cudaMemcpy(d_Input, Input, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	DTanHCUDA <<<dataSize / threadSize + 1, threadSize >>>(d_Input, dataSize);
	if (cudaMemcpy(Output, d_Input, sizeof(double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Input);
		exit(0);
	}
	cudaFree(d_Input);
	cudaDeviceSynchronize();
}

void MSE_CUDA(long double *Predicted, long double *Expected, long double *Output, int dataSize, int threadSize){
	long double* d_Predicted, * d_Expected;
	if (cudaMalloc((void**)&d_Predicted, sizeof(long double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if(cudaMalloc((void**)&d_Expected, sizeof(long double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		cudaFree(d_Predicted);
		exit(0);
	}
	if (cudaMemcpy(d_Predicted, Predicted, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess || cudaMemcpy(d_Expected, Expected, sizeof(long double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Predicted); cudaFree(d_Expected);
		exit(0);
	}
	MSECUDA<<<dataSize/threadSize + 1, threadSize>>>(d_Predicted, d_Expected, dataSize);
	if (cudaMemcpy(Output, d_Predicted, sizeof(long double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Predicted); cudaFree(d_Expected);
		exit(0);
	}
	cudaFree(d_Predicted); cudaFree(d_Expected);
	cudaDeviceSynchronize();
}
void MSE_CUDA(double *Predicted, double *Expected, double *Output, int dataSize, int threadSize){
	double* d_Predicted, * d_Expected;
	if (cudaMalloc((void**)&d_Predicted, sizeof(double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		exit(0);
	}
	if(cudaMalloc((void**)&d_Expected, sizeof(double) * dataSize) != cudaSuccess){
		std::cout << "ERROR getting MEMORY from DEVICE!" << std::endl;
		cudaFree(d_Predicted);
		exit(0);
	}
	if (cudaMemcpy(d_Predicted, Predicted, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess || cudaMemcpy(d_Expected, Expected, sizeof(double) * dataSize, cudaMemcpyHostToDevice) != cudaSuccess){
		std::cout << "ERROR sending DATA to DEVICE!" << std::endl;
		cudaFree(d_Predicted); cudaFree(d_Expected);
		exit(0);
	}
	MSECUDA<<<dataSize/threadSize + 1, threadSize>>>(d_Predicted, d_Expected, dataSize);
	if (cudaMemcpy(Output, d_Predicted, sizeof(double) * dataSize, cudaMemcpyDeviceToHost) != cudaSuccess){
		std::cout << "ERROR sending DATA from DEVICE!" << std::endl;
		cudaFree(d_Predicted); cudaFree(d_Expected);
		exit(0);
	}
	cudaFree(d_Predicted); cudaFree(d_Expected);
	cudaDeviceSynchronize();
}

void _BasicKernel_Cuda_RESET(){
	cudaDeviceReset();
}