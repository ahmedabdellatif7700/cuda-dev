#include "CudaSupport.h"
#include "MatrixAdd.h"

__global__ void AddMatrix2D(const float* a, const float* b, float* output, int width, int height)
{
    const int column = blockIdx.x * blockDim.x + threadIdx.x;
    const int row = blockIdx.y * blockDim.y + threadIdx.y;
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

void LaunchMatrixAdd2D(const float* a, const float* b, float* output, int width, int height, int block_x, int block_y)
{
    const dim3 block(block_x, block_y);
    const dim3 grid((width + block_x - 1) / block_x, (height + block_y - 1) / block_y);
    AddMatrix2D<<<grid, block>>>(a, b, output, width, height);
    CheckCuda(cudaGetLastError(), "Launch AddMatrix2D");
}
