#pragma once

#include "node.hpp"

class IntVal : public Node
{
private:
    std::vector<Node *> children;
    std::variant<int, std::string> value;

public:
    IntVal(std::vector<Node *> children, std::variant<int, std::string> value);
    ~IntVal() override;
    int Evaluate() override;
};