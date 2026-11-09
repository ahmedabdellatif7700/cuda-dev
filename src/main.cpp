#include "FourierImpulse.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(8);
    FourierImpulse(output);
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
}
