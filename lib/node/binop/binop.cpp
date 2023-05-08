#include "binop.hpp"

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType BinOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        std::string op = std::get<std::string>(value);
        int left = std::get<int>(children[0]->Evaluate());
        int right = std::get<int>(children[1]->Evaluate());
        if (op == "+")
            return left + right;
        else if (op == "-")
            return left - right;
        else if (op == "*")
            return left * right;
        else if (op == "/")
            return left / right;
        else if (op == "||")
            return left || right;
        else if (op == "&&")
            return left && right;
        else if (op == "<")
            return left < right;
        else if (op == ">")
            return left > right;
        else if (op == "<=")
            return left <= right;
        else if (op == ">=")
            return left >= right;
        else if (op == "==")
            return left == right;
        else if (op == "!=")
            return left != right;
        else
            throw "Expected PLUS or MINUS or MUL or DIV or OR or AND";
    }
    else
        throw "Expected string";
}