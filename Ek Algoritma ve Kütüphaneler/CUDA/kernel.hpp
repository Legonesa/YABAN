#ifndef KERNEL_HPP
#define KERNEL_HPP

enum Kernel_Calculation{
	Addition = 0,
	Subtraction,
	Multiplication,
	Division
};

static void Calculate_CUDA(int *a, int *b, int *Output, Kernel_Calculation calculation, int dataSize, int threadSize);
static void Calculate_CUDA(double* a, double* b, double* Output, Kernel_Calculation calculation, int dataSize, int threadSize);
static void Calculate_CUDA(long double* a, long double* b, long double* Output, Kernel_Calculation calculation, int dataSize, int threadSize);

static void Sigmoid_CUDA(double *Input, double *Output, int dataSize, int threadSize);
static void Sigmoid_CUDA(long double *Input, long double *Output, int dataSize, int threadSize);
static double Sigmoid_CUDA(double *Input);
static long double Sigmoid_CUDA(long double *Input);

static void DSigmoid_CUDA(double *Input, double *Output, int dataSize, int threadSize);
static void DSigmoid_CUDA(long double *Input, long double *Output, int dataSize, int threadSize);
static double DSigmoid_CUDA(double *Input);
static long double DSigmoid_CUDA(long double *Input);

static void TanH_CUDA(double *Input, double *Output, int dataSize, int threadSize);
static void TanH_CUDA(long double *Input, long double *Output, int dataSize, int threadSize);
static double TanH_CUDA(double *Input);
static long double TanH_CUDA(long double *Input);

static void DTanH_CUDA(double *Input, double *Output, int dataSize, int threadSize);
static void DTanH_CUDA(long double *Input, long double *Output, int dataSize, int threadSize);
static double DTanH_CUDA(double *Input);
static long double DTanH_CUDA(long double *Input);

static void MSE_CUDA(double *Predicted, double *Expected, double *Output, int dataSize, int threadSize);
static void MSE_CUDA(long double *Predicted, long double *Expected, long double *Output, int dataSize, int threadSize);

static void _BasicKernel_Cuda_RESET();

#endif
