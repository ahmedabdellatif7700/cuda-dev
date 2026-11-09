#pragma once
#include <vector>
#include <cuda_runtime.h>
void CpuGpuChunks(std::vector<float>& output);
void LaunchCpuGpuChunks(const float* input, float* output, int count, cudaStream_t stream);
