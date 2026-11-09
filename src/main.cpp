#include "UnrolledReduce.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(1);
    UnrolledReduce(output);
    std::cout << "UnrolledReduce: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
