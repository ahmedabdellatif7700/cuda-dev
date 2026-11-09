#pragma once
#include <vector>
#include <cuda_runtime.h>
void StreamReview(std::vector<float>& output);
void LaunchStreamReview(const float* input, float* output, int count, cudaStream_t stream);
