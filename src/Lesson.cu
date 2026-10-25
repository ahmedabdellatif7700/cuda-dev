#include "Lesson.h"
#include <cuda_runtime.h>
#include <iostream>
#include <vector>

__global__ void AddKernel(const float *a, const float *b,
                          float *c, int n)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;

  if (i < n)
  {
    float x0 = a[i];
    float x1 = b[i];
    float x2 = a[i] + 1.0f;
    float x3 = b[i] + 1.0f;

    for (int j = 0; j < 512; ++j)
    {
      x0 = __fmaf_rn(x0, 0.9999f, 0.0001f);
      x1 = __fmaf_rn(x1, 0.9998f, 0.0002f);
      x2 = __fmaf_rn(x2, 0.9997f, 0.0003f);
      x3 = __fmaf_rn(x3, 0.9996f, 0.0004f);
    }

    c[i] = (x0 + x1) + (x2 + x3);
  }
}

int RunExample()
{
  constexpr int n = 1 << 20;
  constexpr int threads = 256;
  constexpr int blocks = (n + threads - 1) / threads;
  constexpr size_t bytes = n * sizeof(float);

  std::vector<float> a(n, 1.0f);
  std::vector<float> b(n, 2.0f);
  std::vector<float> c(n);

  float *da = nullptr, *db = nullptr, *dc = nullptr;

  cudaMalloc(&da, bytes);
  cudaMalloc(&db, bytes);
  cudaMalloc(&dc, bytes);

  cudaMemcpy(da, a.data(), bytes, cudaMemcpyHostToDevice);
  cudaMemcpy(db, b.data(), bytes, cudaMemcpyHostToDevice);

  AddKernel<<<blocks, threads>>>(da, db, dc, n);
  cudaDeviceSynchronize();

  cudaMemcpy(c.data(), dc, bytes, cudaMemcpyDeviceToHost);

  std::cout << "Blocks: " << blocks << '\n';
  std::cout << "Threads per block: " << threads << '\n';
  std::cout << "Result: " << c[0] << '\n';

  cudaFree(da);
  cudaFree(db);
  cudaFree(dc);
  return 0;
}