#pragma once

#include "node.hpp"

class Block : public Node
{
private:
    std::vector<Node *> children;

public:
    Block(std::vector<Node *> children);
    int Evaluate() override;
};