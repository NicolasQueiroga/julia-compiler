#pragma once

#include <variant>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Node
{
public:
    std::variant<int, std::string> value;
    std::vector<Node *> children;

public:
    virtual ~Node() = default;
    virtual int Evaluate() = 0;
};
