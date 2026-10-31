#pragma once
#include <cuda_runtime.h>
#include <cstddef>
#include <stdexcept>
#include <string>

inline void CheckCuda(cudaError_t error, const char* operation)
{
    if (error != cudaSuccess)
        throw std::runtime_error(std::string(operation) + ": " + cudaGetErrorString(error));
}

// Owns one GPU allocation. Copying is disabled to prevent double-free.
class DeviceBuffer
{
public:
    explicit DeviceBuffer(std::size_t count)
    {
        if (count != 0)
            CheckCuda(cudaMalloc(&data_, count * sizeof(float)), "cudaMalloc");
    }
    ~DeviceBuffer() { if (data_) cudaFree(data_); }
    DeviceBuffer(const DeviceBuffer&) = delete;
    DeviceBuffer& operator=(const DeviceBuffer&) = delete;
    float* data() const { return data_; }
private:
    float* data_ = nullptr;
};
