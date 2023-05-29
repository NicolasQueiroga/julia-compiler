#pragma once

#include "symboltable.hpp"

#include <variant>
#include <string>
#include <vector>

using ValueType = std::variant<int, std::string>;
class Node
{
protected:
    std::variant<int, std::string> value;
    std::vector<Node *> children;
    static int label;
    int index;

public:
    Node();
    virtual ~Node() = default;
    virtual ValueType Evaluate(SymbolTable *symbolTable=nullptr) = 0;
};
