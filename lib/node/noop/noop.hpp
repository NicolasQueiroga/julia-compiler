#pragma once

#include "node.hpp"

class NoOp : public Node
{
public:
    ValueType Evaluate() override;
};