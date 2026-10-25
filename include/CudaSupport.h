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

// Keep the lessons' allocation sizes and launch dimensions bounded.
inline void CheckInputs(const float* a, const float* b, float* c, std::size_t n)
{
    if (n > (1u << 24))
        throw std::invalid_argument("This lesson supports at most 2^24 elements");
    if (n != 0 && (!a || !b || !c))
        throw std::invalid_argument("A non-empty array needs a valid pointer");
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
