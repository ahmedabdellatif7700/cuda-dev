#include "CudaSupport.h"
#include "SparseProduct.h"
#include <cusparse.h>
void SparseProduct(std::vector<float>& output)
{
    const int row_offsets[3] = {0, 1, 2}, column_indices[2] = {0, 1};
    const float values[2] = {2, 3}, input[2] = {1, 1};
    int *rows, *columns;
    CheckCuda(cudaMalloc(&rows, sizeof(row_offsets)), "CSR rows");
    CheckCuda(cudaMalloc(&columns, sizeof(column_indices)), "CSR columns");
    DeviceBuffer a(2), x(2), y(2);
    CheckCuda(cudaMemcpy(rows, row_offsets, sizeof(row_offsets), cudaMemcpyHostToDevice), "Copy CSR rows");
    CheckCuda(cudaMemcpy(columns, column_indices, sizeof(column_indices), cudaMemcpyHostToDevice), "Copy CSR columns");
    CheckCuda(cudaMemcpy(a.data(), values, sizeof(values), cudaMemcpyHostToDevice), "Copy CSR values");
    CheckCuda(cudaMemcpy(x.data(), input, sizeof(input), cudaMemcpyHostToDevice), "Copy vector");
    cusparseHandle_t handle;
    cusparseCreate(&handle);
    cusparseSpMatDescr_t matrix;
    cusparseDnVecDescr_t vector_x, vector_y;
    cusparseCreateCsr(&matrix, 2, 2, 2, rows, columns, a.data(), CUSPARSE_INDEX_32I,
                      CUSPARSE_INDEX_32I, CUSPARSE_INDEX_BASE_ZERO, CUDA_R_32F);
    cusparseCreateDnVec(&vector_x, 2, x.data(), CUDA_R_32F);
    cusparseCreateDnVec(&vector_y, 2, y.data(), CUDA_R_32F);
    const float alpha = 1.0f, beta = 0.0f;
    std::size_t workspace_bytes = 0;
    if (cusparseSpMV_bufferSize(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, &alpha,
        matrix, vector_x, &beta, vector_y, CUDA_R_32F, CUSPARSE_SPMV_ALG_DEFAULT, &workspace_bytes)
        != CUSPARSE_STATUS_SUCCESS) throw std::runtime_error("SpMV workspace query");
    void* workspace = nullptr;
    if (workspace_bytes > 0) CheckCuda(cudaMalloc(&workspace, workspace_bytes), "SpMV workspace");
    if (cusparseSpMV(handle, CUSPARSE_OPERATION_NON_TRANSPOSE, &alpha, matrix, vector_x,
        &beta, vector_y, CUDA_R_32F, CUSPARSE_SPMV_ALG_DEFAULT, workspace)
        != CUSPARSE_STATUS_SUCCESS) throw std::runtime_error("SpMV failed");
    CheckCuda(cudaMemcpy(output.data(), y.data(), sizeof(values), cudaMemcpyDeviceToHost), "Copy SpMV");
    if (workspace) cudaFree(workspace);
    cusparseDestroyDnVec(vector_x); cusparseDestroyDnVec(vector_y);
    cusparseDestroySpMat(matrix); cusparseDestroy(handle);
    cudaFree(rows); cudaFree(columns);
}
