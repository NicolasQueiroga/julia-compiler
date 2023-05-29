#pragma once

#include "node.hpp"
#include "functable.hpp"

class FuncCall : public Node, public FuncTable
{
private:
    std::string func_name;
    std::vector<Node *> children;

public:
    FuncCall(std::string func_name, std::vector<Node *> children);
    ValueType Evaluate(SymbolTable *symbolTable = nullptr) override;
};