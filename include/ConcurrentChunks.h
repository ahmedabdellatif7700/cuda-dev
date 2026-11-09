#pragma once
#include <vector>
#include <cuda_runtime.h>
void ConcurrentChunks(std::vector<float>& output);
void LaunchConcurrentChunks(const float* input, float* output, int count, cudaStream_t stream);
