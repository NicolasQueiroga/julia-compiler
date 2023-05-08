#pragma once

#include "node.hpp"
#include "symboltable.hpp"

class VarDec : public Node, public SymbolTable
{
private:
    std::string type;
    std::string value;
    std::vector<Node *> children;

public:
    VarDec(std::string type, std::string value, std::vector<Node *> children);
    ValueType Evaluate() override;
};
