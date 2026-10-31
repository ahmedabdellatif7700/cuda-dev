#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

void Run(std::size_t n, int threads, int iterations, bool vectorized);

unsigned long long Number(const char* text)
{
    std::string value(text);
    if (value.empty() || value.find_first_not_of("0123456789") != std::string::npos)
        throw std::invalid_argument("Expected an unsigned integer: " + value);
    return std::stoull(value);
}

int main(int argc, char** argv)
{
    try {
        const std::string kernel = argc > 1 ? argv[1] : "scalar";
        if (kernel == "--help") {
            std::cout << "Usage: main [scalar|vectorized|check] [elements=4194304] [threads=256] [iterations=100]\n";
            return 0;
        }
        if (argc > 5 || (kernel != "scalar" && kernel != "vectorized" && kernel != "check"))
            throw std::invalid_argument("Use --help for usage");
        const auto n = argc > 2 ? Number(argv[2]) : 4194304ULL;
        const auto threads = argc > 3 ? Number(argv[3]) : 256ULL;
        const auto iterations = argc > 4 ? Number(argv[4]) : 100ULL;
        if (n > (1u << 24) || threads == 0 || threads > 1024 || iterations == 0 || iterations > 100000)
            throw std::invalid_argument("Limits: elements <= 2^24, threads 1..1024, iterations 1..100000");
        if (kernel == "check") {
            for (bool v : {false, true})
                for (std::size_t size : {0u, 1u, 2u, 3u, 4u, 5u, 255u, 256u, 257u, 1023u, 1025u, 65537u})
                    Run(size, int(threads), 1, v);
        } else Run(std::size_t(n), int(threads), int(iterations), kernel == "vectorized");
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
