#pragma once

#include "node.hpp"

class FuncDec : public Node
{
    friend class FuncCall;

protected:
    std::string func_type;
    std::string func_name;
    std::vector<Node *> params;
    std::vector<Node *> children;

public:
    FuncDec(std::string func_type, std::string func_name, std::vector<Node *> params, std::vector<Node *> children);
    ValueType Evaluate(SymbolTable *symbolTable = nullptr) override;
    std::vector<Node *> getParams();
    std::vector<Node *> getChildren();
};