#include "binop.hpp"
#include "utils.hpp"
#include <iostream>

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType BinOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        std::string op = std::get<std::string>(value);
        ValueType left = children[0]->Evaluate();
        ValueType right = children[1]->Evaluate();

        if (op == ".")
        {
            if (std::holds_alternative<int>(left))
                left = std::to_string(std::get<int>(left));
            if (std::holds_alternative<int>(right))
                right = std::to_string(std::get<int>(right));
            return std::get<std::string>(left) + std::get<std::string>(right);
        }
        else if (op == "+")
        {
            if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right))
                return std::get<std::string>(left) + std::get<std::string>(right);
            else if (std::holds_alternative<int>(left) && std::holds_alternative<std::string>(right))
                return std::to_string(std::get<int>(left)) + std::get<std::string>(right);
            else if (std::holds_alternative<std::string>(left) && std::holds_alternative<int>(right))
                return std::get<std::string>(left) + std::to_string(std::get<int>(right));
            else
                throw "Invalid operands for +";
        }
        else
        {
            if (op == "-" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) - std::get<int>(right);
            else if (op == "*" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) - std::get<int>(right);
            else if (op == "/" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) - std::get<int>(right);
            else if (op == "||" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) - std::get<int>(right);
            else if (op == "&&" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                return std::get<int>(left) - std::get<int>(right);
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
    }
    else
        throw "Expected string";
}