#include "ThreadMapping.h"
#include "VectorAdd.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    const int block_count = 2;
    const int threads_per_block = 32;
    const int element_count = block_count * threads_per_block;

    try
    {
        // CPU: allocate host arrays and prepare the input values.
        std::cout << "CPU: prepare inputs\n";
        std::vector<float> indices(element_count);
        std::vector<float> input_a(element_count);
        std::vector<float> input_b(element_count, 10.0f);
        std::vector<float> output(element_count);

        // Prepare host inputs: A[index] = index and B[index] = 10.
        for (int index = 0; index < element_count; ++index)
            input_a[index] = static_cast<float>(index);

        // The mapping kernel returns blockIdx.x * blockDim.x + threadIdx.x.
        // Its PTX is generated in build/assembly/thread_mapping.ptx.
        ThreadMapping(indices, block_count, threads_per_block);
        VectorAdd(input_a, input_b, output, threads_per_block);

        // Print returned data by logical block/thread ownership.
        // Display order does not reveal GPU execution order or SM placement.
        std::cout << "CPU: print returned results\n\n";
        for (int block = 0; block < block_count; ++block)
        {
            const int first_index = block * threads_per_block;
            std::cout << "Block " << block << '\n';

            std::cout << "Thread: ";
            for (int thread = 0; thread < threads_per_block; ++thread)
                std::cout << std::setw(4) << thread;
            std::cout << '\n';

            std::cout << "Global: ";
            for (int thread = 0; thread < threads_per_block; ++thread)
                std::cout << std::setw(4) << indices[first_index + thread];
            std::cout << '\n';

            std::cout << "A:      ";
            for (int thread = 0; thread < threads_per_block; ++thread)
                std::cout << std::setw(4) << input_a[first_index + thread];
            std::cout << '\n';

            std::cout << "B:      ";
            for (int thread = 0; thread < threads_per_block; ++thread)
                std::cout << std::setw(4) << input_b[first_index + thread];
            std::cout << '\n';

            std::cout << "A + B:  ";
            for (int thread = 0; thread < threads_per_block; ++thread)
                std::cout << std::setw(4) << output[first_index + thread];
            std::cout << "\n\n";
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
