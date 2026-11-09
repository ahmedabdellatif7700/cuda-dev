#include "CudaSupport.h"
#include "SynchronizedExchange.h"

__global__ void SynchronizedExchangeKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd6];  // Read global data.
    // bar.sync 0;  // Block-wide barrier.
    // st.global.f32 [%rd7], %f2;  // Write global data.
    __shared__ float values[256];
    const int lane = threadIdx.x;
    values[lane] = input[lane];
    __syncthreads();
    output[lane] = values[(lane + 1) % 256];
}

void LaunchSynchronizedExchange(const float* input, float* output, int count)
{
    SynchronizedExchangeKernel<<<1, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch SynchronizedExchange");
}
