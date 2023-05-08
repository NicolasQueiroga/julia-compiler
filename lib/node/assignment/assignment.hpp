#pragma once

#include "node.hpp"
#include "symboltable.hpp"

class Assignment : public Node, public SymbolTable
{
private:
    std::vector<Node *> children;
    std::variant<int, std::string> value;

public:
    Assignment(std::vector<Node *> children, std::variant<int, std::string> value);
    ValueType Evaluate() override;
};