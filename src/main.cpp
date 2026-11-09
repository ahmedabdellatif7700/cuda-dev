#include "RandomUniform.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(8);
    RandomUniform(output);
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
}
