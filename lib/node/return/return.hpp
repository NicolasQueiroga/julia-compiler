#pragma once

#include "node.hpp"

class Return : public Node
{
private:
    std::vector<Node *> children;

public:
    Return(std::vector<Node *> children);
    ValueType Evaluate() override;
};