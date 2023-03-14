#pragma once

#include "node.hpp"

class NoOp : public Node
{
public:
    int Evaluate() override;
};