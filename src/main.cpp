#include "IdeaBlocks.h"
#include <iomanip>
#include <iostream>
#include <vector>
int main()
{
    std::vector<unsigned short> output(4);
    IdeaBlocks(output);
    std::cout << "IDEA encrypted words: ";
    for (unsigned short word : output)
        std::cout << std::hex << std::setw(4) << std::setfill('0') << word << ' ';
    std::cout << '\n';
}
