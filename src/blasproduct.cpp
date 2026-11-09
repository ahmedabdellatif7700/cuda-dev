#include "CudaSupport.h"
#include "BlasProduct.h"
#include <cublas_v2.h>
void BlasProduct(std::vector<float>& output)
{
    const float matrix[4] = {1, 2, 3, 4};
    const float identity[4] = {1, 0, 0, 1};
    DeviceBuffer a(4), b(4), c(4);
    CheckCuda(cudaMemcpy(a.data(), matrix, sizeof(matrix), cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(b.data(), identity, sizeof(identity), cudaMemcpyHostToDevice), "Copy B");
    cublasHandle_t handle;
    if (cublasCreate(&handle) != CUBLAS_STATUS_SUCCESS) throw std::runtime_error("Create cuBLAS handle");
    const float alpha = 1.0f, beta = 0.0f;
    const auto status = cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, 2, 2, 2,
                                  &alpha, a.data(), 2, b.data(), 2, &beta, c.data(), 2);
    if (status != CUBLAS_STATUS_SUCCESS) throw std::runtime_error("SGEMM failed");
    CheckCuda(cudaMemcpy(output.data(), c.data(), 4 * sizeof(float), cudaMemcpyDeviceToHost), "Copy product");
    cublasDestroy(handle);
}
