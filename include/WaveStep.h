#pragma once
#include <vector>
void WaveStep(std::vector<float>& output);
void LaunchWaveStep(const float* input, float* output, int count);
