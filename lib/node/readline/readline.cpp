#include "readline.hpp"
#include "assembler.hpp"
#include <iostream>

ValueType ReadLine::Evaluate(SymbolTable *symbolTable)
{
    std::string line;
    std::cin >> line;
    return std::stoi(line);
}