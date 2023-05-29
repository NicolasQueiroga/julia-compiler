#pragma once

#include "node.hpp"

class IntVal : public Node
{
private:
    std::vector<Node *> children;
    std::variant<int, std::string> value;

public:
    IntVal(std::vector<Node *> children, std::variant<int, std::string> value);
    ValueType Evaluate(SymbolTable *symbolTable=nullptr) override;
};