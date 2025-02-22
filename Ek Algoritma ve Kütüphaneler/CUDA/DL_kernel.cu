#include <iostream>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>
#include "DL_kernel.hpp"

__device__ long double DL_Sigmoid(long double i){
	return 1 / (1 + exp((float)-i));
}
__device__ long double DL_TanH(long double i){
	return (exp((float)i) - exp((float)-i)) / (exp((float)i) + exp((float)-i));
}
__device__ long double DL_DTanH(long double i) {
    return 1 - (((exp((float)i) - exp((float)-i)) / (exp((float)i) + exp((float)-i))) * ((exp((float)i) - exp((float)-i)) / (exp((float)i) + exp((float)-i))));
}

__global__ void LSTM_FEEDFORWARD(long double *d_Neurons,long double *d_Input,long double *d_STM,long double *d_LTM,long double *d_IW,long double *d_STMW,long double *d_BW){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < 4){
		switch(idx){
		case 2:
			d_Neurons[idx] = DL_TanH((d_Input[0] * d_IW[idx]) + (d_STM[0] * d_STMW[idx]) + d_BW[idx]);
			break;
		default:
			d_Neurons[idx] = DL_Sigmoid((d_Input[0] * d_IW[idx]) + (d_STM[0] * d_STMW[idx]) + d_BW[idx]);
			break;
		}
	}
}
__global__ void LSTM_FEEDFORWARD_2(long double *d_Neurons,long double *d_LTM, long double *d_oldLTM,long double *d_STM,long double *d_oldSTM){
	d_oldLTM[0] = d_LTM[0];
	d_LTM[0] *= d_Neurons[0];
	d_LTM[0] += d_Neurons[1] * d_Neurons[2];
	d_Neurons[4] = DL_TanH(d_LTM[0]);
	d_oldSTM[0] = d_STM[0];
	d_STM[0] = d_Neurons[3] * d_Neurons[4];
}
__global__ void LSTM_BACKPROPAGATION(long double *d_Neurons,long double *d_Loss,long double *d_STM,long double *d_NINPUT,long double *d_LTM, long double *d_NSD){
	d_Loss[0] = d_STM[0] - d_NINPUT[0];
	d_NSD[0] = d_Loss[0] * d_Neurons[3] * DL_DTanH(d_LTM[0]);
}
__global__ void LSTM_BACKPROPAGATION_2(long double *d_Neurons,long double *d_FGD,long double *d_IGD,long double *d_CGD,long double *d_NSD,long double* d_oldLTM){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < 3){
		switch(idx){
		case 0:
			d_FGD[0] = d_NSD[0] * d_oldLTM[0] * d_Neurons[0] * (1 - d_Neurons[0]);
			break;
		case 1:
			d_IGD[0] = d_NSD[0] * d_Neurons[2] * d_Neurons[1] * (1 - d_Neurons[1]);
			break;
		case 2:
			d_CGD[0] = d_NSD[0] * d_Neurons[1] * (1 - (d_Neurons[2] * d_Neurons[2]));
			break;
		}
	}
}
__global__ void LSTM_UPDATE_WEIGHTS(long double *FGD, long double *IGD, long double *CGD, long double *IW, long double *STMW, long double *BW, long double *oldSTM, long double *learningRate, long double *Input){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < 4){
		switch(idx){
		case 0:
			IW[idx] -= FGD[0] * Input[0] * learningRate[0];
            STMW[idx] -= FGD[0] * oldSTM[0] * learningRate[0];
            BW[idx] -= FGD[0] * learningRate[0];
			break;
		case 1:
			IW[idx] -= IGD[0] * Input[0] * learningRate[0];
            STMW[idx] -= IGD[0] * oldSTM[0] * learningRate[0];
            BW[idx] -= IGD[0] * learningRate[0];
			break;
		default:
			IW[idx] -= CGD[0] * Input[0] * learningRate[0];
            STMW[idx] -= CGD[0] * oldSTM[0] * learningRate[0];
            BW[idx] -= CGD[0] * learningRate[0];
			break;
		}
	}
}
__global__ void NN_FEEDFORWARD(long double *d_firstValue,long double *d_secondLayer,long double *d_Weights, int layerSize){
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < layerSize){
		d_secondLayer[idx] += d_firstValue[0] * d_Weights[idx];
	}
}
void CUDA_LSTM_BEGIN(long double *IW, long double *STMW, long double *BW,
			long double **d_LR, long double **d_LTM, long double **d_STM, long double **d_Neurons, long double **d_Loss,
            long double **d_FGD, long double **d_IGD, long double **d_CGD, long double **d_Input, long double **d_IW,
			long double **d_STMW, long double **d_BW, long double **d_oldSTM, long double **d_oldLTM, long double **d_NSD,
			long double **d_NINPUT){
	cudaError_t err;
	err = cudaMalloc((void**)d_FGD, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE FGD!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_IGD, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE IGD!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_CGD, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE CGD!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_IW, sizeof(long double) * 4);
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE IW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_STMW, sizeof(long double) * 4);
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE STMW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_BW, sizeof(long double) * 4);
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE BW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_oldSTM, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE OLDSTM!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_LR, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE LR!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_Input, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE INPUT!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_LTM, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE LTM!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_STM, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE STM!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_Neurons, sizeof(long double) * 5);
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE NEURONS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_Loss, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE LOSS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_oldLTM, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE OLDLTM!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_NSD, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE NSD!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)d_NINPUT, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA CREATE VARIABLE NINPUT!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(*d_IW, IW, sizeof(long double) * 4, cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA SAVE VALUE IW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(*d_STMW, STMW, sizeof(long double) * 4, cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA SAVE VALUE STMW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(*d_BW, BW, sizeof(long double) * 4, cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA SAVE VALUE BW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
}
void CUDA_LSTM_FEEDFORWARD(long double *Input, long double *NInput, long double *d_NINPUT, long double *d_Neurons,long double *d_Input,long double *d_STM,long double *d_LTM,long double *d_IW,long double *d_STMW,long double *d_BW,long double *d_oldSTM,long double *d_oldLTM, int threadSize){
	cudaError_t err = cudaMemcpy(d_Input, Input, sizeof(long double), cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM SAVE INPUT!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(d_NINPUT, NInput, sizeof(long double), cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM SAVE NEXT INPUT!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	LSTM_FEEDFORWARD<<<(4+threadSize -1) / threadSize, threadSize>>>(d_Neurons, d_Input, d_STM, d_LTM, d_IW, d_STMW, d_BW);
	cudaDeviceSynchronize();
	LSTM_FEEDFORWARD_2<<<1, 1>>>(d_Neurons, d_LTM, d_oldLTM, d_STM, d_oldSTM);
	cudaDeviceSynchronize();
}
void CUDA_LSTM_BACKPROPAGATION(long double *d_Neurons, long double *d_oldLTM, long double *d_LTM, long double *d_STM, long double *d_Loss,long double *d_NSD,long double *d_FGD,long double *d_IGD,long double *d_CGD,long double* d_IW,long double* d_STMW,long double* d_BW,long double *d_oldSTM,long double *d_LR,long double *d_Input, long double *d_NINPUT, long double *learningRate, int threadSize){
	cudaError_t err = cudaMemcpy(d_LR, learningRate, sizeof(long double), cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM SAVE LEARNING RATE!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	LSTM_BACKPROPAGATION<<<1, 1>>>(d_Neurons, d_Loss, d_STM, d_NINPUT, d_LTM, d_NSD);
	cudaDeviceSynchronize();
	LSTM_BACKPROPAGATION_2<<<(3+threadSize - 1) / threadSize, threadSize>>>(d_Neurons, d_FGD, d_IGD, d_CGD, d_NSD, d_oldLTM);
	cudaDeviceSynchronize();
	LSTM_UPDATE_WEIGHTS<<<(4+threadSize - 1)/threadSize, threadSize>>>(d_FGD, d_IGD, d_CGD, d_IW, d_STMW, d_BW, d_oldSTM, d_LR, d_Input);
	cudaDeviceSynchronize();
}
void CUDA_LSTM_SAVE_LAST_WEIGHTS(long double *InputWeights,long double *d_IW,long double *STMWeights, long double *d_STMW, long double *BiaS,long double *d_BW){
	cudaError_t err = cudaMemcpy(InputWeights,d_IW,sizeof(long double)*4,cudaMemcpyDeviceToHost);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM SAVE LAST INPUT WEIHGTS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(STMWeights,d_STMW,sizeof(long double)*4,cudaMemcpyDeviceToHost);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM SAVE LAST STM WEIGHTS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(BiaS,d_BW,sizeof(long double)*4,cudaMemcpyDeviceToHost);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM SAVE LAST BIASW!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
}
void CUDA_LSTM_RESET_LTM_STM(long double *d_LTM,long double *d_STM){
	long double ltm_stm = 0;
	cudaError_t err = cudaMemcpy(d_LTM, &ltm_stm, sizeof(long double), cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM RESET LTM!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(d_STM, &ltm_stm, sizeof(long double), cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA LSTM RESET STM!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	cudaDeviceSynchronize();
}
void CUDA_NN_FEEDFORWARD(long double *firstValue,long double *secondLayer,long double *Weights,int secondLayerSize, int threadSize){
	long double *d_firstValue, *d_secondLayer, *d_Weights;
	cudaError_t err = cudaMalloc((void**)&d_firstValue, sizeof(long double));
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD GET MEMORY FIRST VALUE!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)&d_secondLayer, sizeof(long double) * secondLayerSize);
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD GET MEMORY SECOND LAYER!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMalloc((void**)&d_Weights, sizeof(long double) * secondLayerSize);
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD GET MEMORY WEIGHTS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err = cudaMemcpy(d_firstValue, firstValue, sizeof(long double), cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD COPY FIRST VALUE!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err =cudaMemcpy(d_Weights, Weights, sizeof(long double) * secondLayerSize, cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD COPY WEIGHTS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	err =cudaMemcpy(d_secondLayer, secondLayer, sizeof(long double) * secondLayerSize, cudaMemcpyHostToDevice);
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD COPY WEIGHTS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	NN_FEEDFORWARD<<<(secondLayerSize + threadSize -1) / threadSize, threadSize>>>(d_firstValue, d_secondLayer, d_Weights, secondLayerSize);
	err =cudaMemcpy(secondLayer, d_secondLayer, sizeof(long double) * secondLayerSize, cudaMemcpyDeviceToHost);
	if(err != cudaSuccess){
		std::cout << "CUDA NN FEEDFORWARD COPY WEIGHTS!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	cudaFree(d_firstValue); cudaFree(d_secondLayer); cudaFree(d_Weights);
	cudaDeviceSynchronize();
}
long double _getValueCUDA_(long double* Variable){
	long double Output;
	if (Variable == NULL) {
		std::cerr << "Error: Variable is null!" << std::endl;
	}
	cudaError_t err = cudaMemcpy(&Output, Variable, sizeof(long double), cudaMemcpyDeviceToHost);
	if(err != cudaSuccess){
		std::cout << "CUDA GET VALUE!" << std::endl;
		std::cerr << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
		exit(0);
	}
	return Output;
}
void _DLkernel_Cuda_RESET(){
	cudaDeviceReset();
}