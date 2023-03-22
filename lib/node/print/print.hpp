#pragma once

#include "node.hpp"

class Print : public Node
{
private:
    std::vector<Node *> children;

public:
    Print(std::vector<Node *> children);
    int Evaluate() override;
};