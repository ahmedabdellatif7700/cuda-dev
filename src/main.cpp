#include "ShuffleReduce.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(1);
    ShuffleReduce(output);
    std::cout << "ShuffleReduce: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
