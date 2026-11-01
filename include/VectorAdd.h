#pragma once

#include <cstddef>
#include <vector>

// Add equally sized host arrays on the GPU and copy the result back.
void VectorAdd(const std::vector<float>& input_a, const std::vector<float>& input_b,
               std::vector<float>& output, int threads_per_block);

// Launch on device arrays. The runtime caller checks element_counts and launch parameters.
void LaunchVectorAddScalar(const float* input_a, const float* input_b, float* output,
                           std::size_t element_count, int threads_per_block);

// Same addition with input_a bounded grid and cyclic element ownership.
void VectorAddCyclic(const std::vector<float>& input_a, const std::vector<float>& input_b,
                     std::vector<float>& output, int threads_per_block, int max_blocks);

void LaunchVectorAddCyclic(const float* input_a, const float* input_b, float* output,
                          std::size_t element_count, int threads_per_block, int max_blocks);
