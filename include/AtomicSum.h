#pragma once
#include <vector>
void AtomicSum(std::vector<float>& output);
void LaunchAtomicSum(const float* input, float* output, int count);
