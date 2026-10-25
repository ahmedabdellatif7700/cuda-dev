#include "Lesson.h"
#include "CudaSupport.h"


namespace
{
constexpr int threads = 256;

__global__ void AddKernel(const float* a, const float* b, float* c, std::size_t n)
{
    const std::size_t i = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    if (i < n)
        c[i] = a[i] + b[i];
}
}

void VectorAdd(const float* a, const float* b, float* c, std::size_t n)
{
    CheckInputs(a, b, c, n);
    if (n == 0) return;
    const std::size_t bytes = n * sizeof(float);
    DeviceBuffer da(n), db(n), dc(n);
    CheckCuda(cudaMemcpy(da.data(), a, bytes, cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(db.data(), b, bytes, cudaMemcpyHostToDevice), "Copy B");
    const unsigned blocks = unsigned((n + threads - 1) / threads);
    AddKernel<<<blocks, threads>>>(da.data(), db.data(), dc.data(), n);
    CheckCuda(cudaGetLastError(), "Launch AddKernel");
    CheckCuda(cudaDeviceSynchronize(), "Execute AddKernel");
    CheckCuda(cudaMemcpy(c, dc.data(), bytes, cudaMemcpyDeviceToHost), "Copy result");
}
