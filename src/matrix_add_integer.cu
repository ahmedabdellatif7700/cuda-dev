#include "CudaSupport.h"
#include "MatrixAdd.h"

__global__ void AddMatrixInteger(const int* a, const int* b, int* output, int width, int height)
{
    const int column = blockIdx.x * blockDim.x + threadIdx.x;
    const int row = blockIdx.y * blockDim.y + threadIdx.y;
    if (column < width && row < height)
    {
        const int index = row * width + column;
        // Selected generated PTX; address/branch setup omitted.
        // ld.global.u32 %r12, [%rd8];  // Load an input element.
        // ld.global.u32 %r13, [%rd6];  // Load an input element.
        // add.s32 %r14, %r12, %r13;  // Add the two input values.
        // st.global.u32 [%rd10], %r14;  // Store this output element.
        output[index] = a[index] + b[index];
    }
}

void LaunchMatrixAddInteger(const int* a, const int* b, int* output, int width, int height, int block_x, int block_y)
{
    const dim3 block(block_x, block_y);
    const dim3 grid((width + block_x - 1) / block_x, (height + block_y - 1) / block_y);
    AddMatrixInteger<<<grid, block>>>(a, b, output, width, height);
    CheckCuda(cudaGetLastError(), "Launch AddMatrixInteger");
}
