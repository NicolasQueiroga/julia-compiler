#pragma once

#include "node.hpp"
#include "functable.hpp"

class FuncDec : public Node, public FuncTable
{
private:
    std::string func_type;
    std::string func_name;
    std::vector<Node *> params;
    std::vector<Node *> children;

public:
    FuncDec(std::string func_type, std::string func_name, std::vector<Node *> params, std::vector<Node *> children);
    ValueType Evaluate() override;
};