#include "CudaSupport.h"
#include "MatrixAdd.h"

__global__ void AddMatrixPairs(const float* a, const float* b, float* output, int width, int height)
{
    const int column = blockIdx.x * (2 * blockDim.x) + threadIdx.x;
    const int row = blockIdx.y;
    if (row < height && column < width)
    {
        const int index = row * width + column;
        // Selected generated PTX; address/branch setup omitted.
        // ld.global.f32 %f1, [%rd9];  // Load an input element.
        // ld.global.f32 %f2, [%rd8];  // Load an input element.
        // add.f32 %f3, %f2, %f1;  // Add the two input values.
        // st.global.f32 [%rd10], %f3;  // Store this output element.
        output[index] = a[index] + b[index];
        if (column + blockDim.x < width)
            output[index + blockDim.x] = a[index + blockDim.x] + b[index + blockDim.x];
    }
}

void LaunchMatrixAddPairs(const float* a, const float* b, float* output, int width, int height, int threads)
{
    const dim3 grid((width + 2 * threads - 1) / (2 * threads), height);
    AddMatrixPairs<<<grid, threads>>>(a, b, output, width, height);
    CheckCuda(cudaGetLastError(), "Launch AddMatrixPairs");
}
