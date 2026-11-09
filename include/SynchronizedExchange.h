#pragma once
#include <vector>
void SynchronizedExchange(std::vector<float>& output);
void LaunchSynchronizedExchange(const float* input, float* output, int count);
