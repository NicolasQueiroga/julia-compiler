#pragma once

#include <variant>
#include <string>
#include <vector>
#include <utility>

class Node
{
protected:
    std::variant<int, std::string> value;
    std::vector<Node *> children;

public:
    virtual ~Node() = default;
    virtual int Evaluate() = 0;
};
