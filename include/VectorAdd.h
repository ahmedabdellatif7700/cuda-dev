#pragma once

#include <cstddef>
#include <vector>

// Host function: copy inputs to the GPU, add them, and copy sums to output.
// The caller must provide equally sized input and output vectors.
// Thread i computes output[i] = input_a[i] + input_b[i].
void VectorAdd(const std::vector<float>& input_a, const std::vector<float>& input_b,
               std::vector<float>& output, int threads_per_block);

// CUDA launch wrapper: all three pointers refer to device arrays.
// Launch enough blocks to cover element_count; extra threads skip the work.
void LaunchVectorAddScalar(const float* input_a, const float* input_b, float* output,
                           std::size_t element_count, int threads_per_block);
