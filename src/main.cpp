#include "PaddedTranspose.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(64);
    PaddedTranspose(output);
    std::cout << "PaddedTranspose: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
