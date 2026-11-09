#include "CudaSupport.h"
#include "TransposeMatrix.h"

__global__ void TransposeMatrixKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // st.global.f32 [%rd8], %f1;  // Write global data.
    const int column = blockIdx.x * blockDim.x + threadIdx.x;
    const int row = blockIdx.y * blockDim.y + threadIdx.y;
    if (column < 8 && row < 8) output[column * 8 + row] = input[row * 8 + column];
}

void LaunchTransposeMatrix(const float* input, float* output, int count)
{
    TransposeMatrixKernel<<<dim3(2, 2), dim3(4, 4)>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch TransposeMatrix");
}
