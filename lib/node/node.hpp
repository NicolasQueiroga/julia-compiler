#pragma once

#include <variant>
#include <string>
#include <vector>

using ValueType = std::variant<int, std::string>;
class Node
{
protected:
    std::variant<int, std::string> value;
    std::vector<Node *> children;

public:
    virtual ~Node() = default;
    virtual ValueType Evaluate() = 0;
};
