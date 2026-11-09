#include "CudaSupport.h"
#include "NestedReduce.h"
#include "ChildSum.cuh"
__global__ void NestedReduceKernel(const float* input, float* output, int count)
{
    if (blockIdx.x == 0 && threadIdx.x == 0)
        ChildSum<<<1, 256>>>(input, output, count);
}

void LaunchNestedReduce(const float* input, float* output, int count)
{
    NestedReduceKernel<<<1, 1>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch NestedReduce");
}
