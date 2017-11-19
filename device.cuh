#ifndef __DEVICE_CUH__
	#define __DEVICE_CUH__

	#include "assembly.h"
	#include "structure.h"
	#include <cuda_runtime.h>

	__device__ double datomicAdd(double* address, double val);

	__global__ void MatAdd(double kg[], double kl[], int dof[], int sizekl, int sizekg);
#endif