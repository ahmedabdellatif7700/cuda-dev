#pragma once
#include <vector>
void SharedExchange(std::vector<float>& output);
void LaunchSharedExchange(const float* input, float* output, int count);
