#pragma once

#include "node.hpp"

class ReadLine : public Node
{
public:
    ValueType Evaluate(SymbolTable *symbolTable=nullptr) override;
};
