#pragma once

#include <cstddef>
#include <span>

// Add equally sized host arrays on the GPU and copy the result back.
void VectorAdd(std::span<const float> a, std::span<const float> b,
               std::span<float> c, int threads);

// Launch on device arrays. The runtime caller checks sizes and launch parameters.
void LaunchVectorAddScalar(const float* a, const float* b, float* c,
                           std::size_t n, int threads);
