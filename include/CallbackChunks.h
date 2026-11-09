#pragma once
#include <vector>
#include <cuda_runtime.h>
void CallbackChunks(std::vector<float>& output);
void LaunchCallbackChunks(const float* input, float* output, int count, cudaStream_t stream);
