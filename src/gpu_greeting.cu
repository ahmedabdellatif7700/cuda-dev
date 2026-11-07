#include "CudaSupport.h"
#include "GpuGreeting.h"

#include <cstdio>

__global__ void PrintGpuGreeting()
{
    // Selected PTX from make ptx; printf argument setup is omitted.
    // mov.u32 %r1, %tid.x;       // Read the local thread index.
    // setp.ne.s32 %p1, %r1, 5;   // Test whether this is not thread 5.
    // @%p1 bra $L__BB0_2;        // Other threads skip the printf path.
    if (threadIdx.x == 5)
        printf("Hello World from GPU thread %u!\n", threadIdx.x);
}

void GpuGreeting()
{
    PrintGpuGreeting<<<1, 10>>>();
    CheckCuda(cudaGetLastError(), "Launch PrintGpuGreeting");
    cudaDeviceSynchronize();
}
