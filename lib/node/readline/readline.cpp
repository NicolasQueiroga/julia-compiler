#include "readline.hpp"
#include "assembler.hpp"
#include <iostream>

ValueType ReadLine::Evaluate()
{
    std::string line;
    std::cin >> line;
    return std::stoi(line);
}