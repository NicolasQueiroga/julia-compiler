#pragma once

#include "node.hpp"

class UnOp : public Node
{
private:
    std::vector<Node *> children;
    std::variant<int, std::string> value;

public:
    UnOp(std::vector<Node *> children, std::variant<int, std::string> value);
    ValueType Evaluate(SymbolTable *symbolTable=nullptr) override;
};