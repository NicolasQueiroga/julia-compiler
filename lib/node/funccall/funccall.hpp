#pragma once

#include "node.hpp"

class FuncCall : public Node
{
private:
    std::string func_name;
    std::vector<Node *> children;

public:
    FuncCall(std::string func_name, std::vector<Node *> children);
    ValueType Evaluate() override;
};