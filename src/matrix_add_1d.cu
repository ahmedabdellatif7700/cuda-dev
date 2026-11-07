#include "CudaSupport.h"
#include "MatrixAdd.h"

__global__ void AddMatrix1D(const float* a, const float* b, float* output, int width, int height)
{
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < width * height)
        // Selected generated PTX; address/branch setup omitted.
        // ld.global.f32 %f1, [%rd8];  // Load an input element.
        // ld.global.f32 %f2, [%rd6];  // Load an input element.
        // add.f32 %f3, %f2, %f1;  // Add the two input values.
        // st.global.f32 [%rd10], %f3;  // Store this output element.
        output[index] = a[index] + b[index];
}

void LaunchMatrixAdd1D(const float* a, const float* b, float* output, int width, int height, int threads)
{
    const int blocks = (width * height + threads - 1) / threads;
    AddMatrix1D<<<blocks, threads>>>(a, b, output, width, height);
    CheckCuda(cudaGetLastError(), "Launch AddMatrix1D");
}
