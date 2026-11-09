#pragma once
#include <vector>
#include <cuda_runtime.h>
void StreamChunks(std::vector<float>& output);
void LaunchStreamChunks(const float* input, float* output, int count, cudaStream_t stream);
