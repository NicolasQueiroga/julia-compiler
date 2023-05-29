#pragma once

#include "node.hpp"

class StrVal : public Node
{
private:
    std::vector<Node *> children;
    ValueType value;

public:
    StrVal(std::vector<Node *> children, ValueType value);
    ValueType Evaluate(SymbolTable *symbolTable=nullptr) override;
};