#include "VectorAdd.h"

#include <cuda_runtime.h>
#include <iostream>

// GPU: each thread adds one pair of elements.
__global__ void VectorAddKernel(
    const float *a,
    const float *b,
    float *c)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

// CPU: prepares data and launches GPU work.
int RunVectorAdd()
{
    constexpr int count = 8;
    constexpr int bytes = count * sizeof(float);

    float a[count] = {0, 1, 2, 3, 4, 5, 6, 7};
    float b[count] = {0, 2, 4, 6, 8, 10, 12, 14};
    float c[count];

    // Allocate GPU memory.
    float *deviceA;
    float *deviceB;
    float *deviceC;

    cudaMalloc(&deviceA, bytes);
    cudaMalloc(&deviceB, bytes);
    cudaMalloc(&deviceC, bytes);

    // Copy inputs to the GPU.
    cudaMemcpy(deviceA, a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, b, bytes, cudaMemcpyHostToDevice);

    // Launch one block containing eight threads.
    VectorAddKernel<<<1, count>>>(deviceA, deviceB, deviceC);

    // Wait for the GPU to finish.
    cudaDeviceSynchronize();

    // Copy the result back to the CPU.
    cudaMemcpy(c, deviceC, bytes, cudaMemcpyDeviceToHost);

    for (int i = 0; i < count; ++i)
    {
        std::cout << a[i] << " + " << b[i]
                  << " = " << c[i] << '\n';
    }

    // Release GPU memory.
    cudaFree(deviceA);
    cudaFree(deviceB);
    cudaFree(deviceC);

    return 0;
}