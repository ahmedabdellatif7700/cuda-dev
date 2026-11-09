#pragma once
#include <vector>
void PaddedTranspose(std::vector<float>& output);
void LaunchPaddedTranspose(const float* input, float* output, int count);
