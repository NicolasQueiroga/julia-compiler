#include <iostream>
#include "readline.hpp"

int ReadLine::Evaluate()
{
    std::string line;
    std::cin >> line;
    return std::stoi(line);
}