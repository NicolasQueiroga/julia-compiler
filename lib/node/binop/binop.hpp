#pragma once

#include "node.hpp"

class BinOp : public Node
{
private:
    std::vector<Node *> children;
    std::variant<int, std::string> value;
    int operateInt(std::string op, int left, int right);
    std::string operateString(std::string op, std::string left, std::string right);

public:
    BinOp(std::vector<Node *> children, std::variant<int, std::string> value);
    ValueType Evaluate() override;
};
