#include <cstddef>
#include <exception>
#include <iostream>

void RunVectorAddExamples(std::size_t count, int threads, int repetitions);

int main()
{
    // Change one setting at a time, then compare the two kernels.
    // The extra three elements exercise the vectorized kernel's tail handling.
    constexpr std::size_t element_count = 4 * 1024 * 1024 + 3;
    constexpr int threads_per_block = 256;
    constexpr int repetitions = 100;

    try
    {
        RunVectorAddExamples(element_count, threads_per_block, repetitions);
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
