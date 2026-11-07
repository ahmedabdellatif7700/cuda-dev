#include "CudaSupport.h"
#include "MatrixAdd.h"

__global__ void AddMatrixRows(const float* a, const float* b, float* output, int width, int height)
{
    const int column = blockIdx.x * blockDim.x + threadIdx.x;
    const int row = blockIdx.y;
    if (column < width && row < height)
    {
        const int index = row * width + column;
        // Selected generated PTX; address/branch setup omitted.
        // ld.global.f32 %f1, [%rd8];  // Load an input element.
        // ld.global.f32 %f2, [%rd6];  // Load an input element.
        // add.f32 %f3, %f2, %f1;  // Add the two input values.
        // st.global.f32 [%rd10], %f3;  // Store this output element.
        output[index] = a[index] + b[index];
    }
}

void LaunchMatrixAddRows(const float* a, const float* b, float* output, int width, int height, int threads)
{
    const dim3 grid((width + threads - 1) / threads, height);
    AddMatrixRows<<<grid, threads>>>(a, b, output, width, height);
    CheckCuda(cudaGetLastError(), "Launch AddMatrixRows");
}
