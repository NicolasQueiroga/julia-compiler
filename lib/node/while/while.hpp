#pragma once

#include "node.hpp"

class While : public Node
{
private:
    std::vector<Node *> children;

public:
    While(std::vector<Node *> children);
    ValueType Evaluate() override;
};
