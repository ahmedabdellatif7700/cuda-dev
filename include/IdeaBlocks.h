#pragma once
#include <vector>
void IdeaBlocks(std::vector<unsigned short>& output);
void UploadIdeaKeys(const unsigned short* keys);
void LaunchIdeaBlocks(const unsigned short* input, unsigned short* output, int blocks);
