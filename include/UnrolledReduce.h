#pragma once
#include <vector>
void UnrolledReduce(std::vector<float>& output);
void LaunchUnrolledReduce(const float* input, float* output, int count);
