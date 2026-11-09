#include "CudaSupport.h"
#include "PaddedTranspose.h"

__global__ void PaddedTransposeKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd6];  // Read global data.
    // bar.sync 0;  // Block-wide barrier.
    // st.global.f32 [%rd7], %f2;  // Write global data.
    __shared__ float tile[8][9];
    const int column = threadIdx.x;
    const int row = threadIdx.y;
    tile[row][column] = input[row * 8 + column];
    __syncthreads();
    output[row * 8 + column] = tile[column][row];
}

void LaunchPaddedTranspose(const float* input, float* output, int count)
{
    PaddedTransposeKernel<<<1, dim3(8, 8)>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch PaddedTranspose");
}
