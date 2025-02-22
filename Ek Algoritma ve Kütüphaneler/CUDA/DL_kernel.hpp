#ifndef DL_KERNEL_HPP
#define DL_KERNEL_HPP

void CUDA_LSTM_BEGIN(long double *IW, long double *STMW, long double *BW,
			long double **d_LR, long double **d_LTM, long double **d_STM, long double **d_Neurons, long double **d_Loss,
            long double **d_FGD, long double **d_IGD, long double **d_CGD, long double **d_Input, long double **d_IW,
			long double **d_STMW, long double **d_BW, long double **d_oldSTM, long double **d_oldLTM, long double **d_NSD,
			long double **d_NINPUT);
void CUDA_LSTM_RESET_LTM_STM(long double *d_LTM, long double *d_STM);
void CUDA_LSTM_FEEDFORWARD(long double *Input, long double *NInput, long double *d_NINPUT, long double *d_Neurons, long double *d_Input, long double *d_STM, long double *d_LTM, long double *d_IW, long double *d_STMW, long double *d_BW, long double *d_oldSTM, long double *d_oldLTM, int threadSize);
void CUDA_LSTM_BACKPROPAGATION(long double *d_Neurons, long double *d_oldLTM, long double *d_LTM, long double *d_STM, long double *d_Loss, long double *d_NSD, long double *d_FGD, long double *d_IGD, long double *d_CGD, long double* d_IW,long double* d_STMW,long double* d_BW, long double *d_oldSTM, long double *d_LR, long double *d_Input, long double *d_NINPUT, long double *learningRate, int threadSize);
void CUDA_LSTM_SAVE_LAST_WEIGHTS(long double *InputWeights, long double *d_IW, long double *STMWeights, long double *d_STMW, long double *BiaS, long double *d_BW);

void CUDA_NN_FEEDFORWARD(long double *firstValue, long double *secondLayer, long double *Weights,int secondLayerSize, int threadSize);

long double _getValueCUDA_(long double* Variable);
void _DLkernel_Cuda_RESET();
#endif
