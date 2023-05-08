#pragma once

#include "node.hpp"
#include "symboltable.hpp"

class Identifier : public Node, public SymbolTable
{
private:
    std::variant<int, std::string> value;

public:
    Identifier(std::variant<int, std::string> value);
    ValueType Evaluate() override;
};