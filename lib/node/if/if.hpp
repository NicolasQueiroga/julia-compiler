#pragma once

#include "node.hpp"

class If : public Node
{
private:
    std::vector<Node *> children;
    size_t size;

public:
    If(std::vector<Node *> children);
    ValueType Evaluate() override;
};
