#include "ScaleValues.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(1024);
    ScaleValues(output);
    std::cout << "ScaleValues: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
