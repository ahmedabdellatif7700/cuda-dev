#include <cuda_runtime.h>
#include <cstdio>
__global__ void greeting() { printf("Hello World from GPU thread %u!\n", threadIdx.x); }
int main() { greeting<<<1,10>>>(); cudaDeviceReset(); return 0; }
