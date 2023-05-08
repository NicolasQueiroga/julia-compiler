#pragma once

#include "node.hpp"

class BinOp : public Node
{
private:
    std::vector<Node *> children;
    std::variant<int, std::string> value;

public:
    BinOp(std::vector<Node *> children, std::variant<int, std::string> value);
    ValueType Evaluate() override;
};
