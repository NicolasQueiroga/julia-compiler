#include <iostream>
#include "readline.hpp"

ValueType ReadLine::Evaluate()
{
    std::string line;
    std::cin >> line;
    return std::stoi(line);
}