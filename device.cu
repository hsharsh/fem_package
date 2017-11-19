#include "device.cuh"

__device__ double datomicAdd(double* address, double val){
    unsigned long long int* address_as_ull = (unsigned long long int*) address;
    unsigned long long int old = *address_as_ull, assumed;

    do{
      assumed = old;
      old = atomicCAS(address_as_ull, assumed, __double_as_longlong(val + __longlong_as_double(assumed)));
    } while(assumed != old);

    return __longlong_as_double(old);
}

__global__ void MatAdd(double kg[], double kl[], int dof[], int sizekl, int sizekg){
    int i = blockIdx.x;
    int j = threadIdx.x;
    int k = threadIdx.y;
    datomicAdd( &(kg[dof[i*sizekl + j]*sizekg + dof[i*sizekl + k]]), kl[i*sizekl*sizekl + j*sizekl +k]);
    __syncthreads();
}
