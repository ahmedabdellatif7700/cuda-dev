#include "VectorAdd.h"

#include <exception>
#include <iostream>
#include <vector>

int main()
{
    const int element_count = 65536;
    const int threads_per_block = 256;
    const int max_blocks = 64;

    try
    {
        std::vector<float> input_a(element_count, 1.0f);
        std::vector<float> input_b(element_count, 2.0f);
        std::vector<float> output(element_count);

        VectorAdd(input_a, input_b, output, threads_per_block);

        std::cout << "Scalar: ";
        for (int i = 0; i < 8 && i < element_count; ++i)
            std::cout << output[i] << ' ';
        std::cout << '\n';

        VectorAddCyclic(input_a, input_b, output, threads_per_block, max_blocks);

        std::cout << "Cyclic: ";
        for (int i = 0; i < 8 && i < element_count; ++i)
            std::cout << output[i] << ' ';
        std::cout << '\n';
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
