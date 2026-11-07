#include <cuda_runtime.h>
#include <cstdio>

__global__ void EmptyKernel() {}
int main()
{
    EmptyKernel<<<1, 0>>>();
    printf("Launch error: %s\n", cudaGetErrorString(cudaGetLastError()));
    EmptyKernel<<<1, 32>>>();
    printf("Valid completion: %s\n", cudaGetErrorString(cudaDeviceSynchronize()));
    int count = 0;
    cudaGetDeviceCount(&count);
    printf("Invalid device: %s\n", cudaGetErrorString(cudaSetDevice(count)));
}
