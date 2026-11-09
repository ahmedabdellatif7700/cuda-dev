#include "WaveStep.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(64);
    WaveStep(output);
    std::cout << "WaveStep: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
