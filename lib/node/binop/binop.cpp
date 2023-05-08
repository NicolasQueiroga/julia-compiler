#include "binop.hpp"
#include <type_traits>

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

int BinOp::operateInt(std::string op, int left, int right)
{
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

std::string BinOp::operateString(std::string op, std::string left, std::string right)
{
    if (op == "+" || op == ".")
        return left + right;
    else
        throw "Expected PLUS or OR or AND";
}

ValueType BinOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        std::string op = std::get<std::string>(value);

        if (std::holds_alternative<std::string>(children[0]->Evaluate()) && std::holds_alternative<std::string>(children[1]->Evaluate()))
        {
            std::string left = std::get<std::string>(children[0]->Evaluate());
            std::string right = std::get<std::string>(children[1]->Evaluate());
            return operateString(op, left, right);
        }
        else if (std::holds_alternative<int>(children[0]->Evaluate()) && std::holds_alternative<std::string>(children[1]->Evaluate()))
        {
            std::string left = std::to_string(std::get<int>(children[0]->Evaluate()));
            std::string right = std::get<std::string>(children[1]->Evaluate());
            return operateString(op, left, right);
        }
        else if (std::holds_alternative<std::string>(children[0]->Evaluate()) && std::holds_alternative<int>(children[1]->Evaluate()))
        {
            std::string left = std::get<std::string>(children[0]->Evaluate());
            std::string right = std::to_string(std::get<int>(children[1]->Evaluate()));
            return operateString(op, left, right);
        }
        else
        {
            int left = std::get<int>(children[0]->Evaluate());
            int right = std::get<int>(children[1]->Evaluate());
            return operateInt(op, left, right);
        }
        
        return 0;
    }
    else
        throw "Expected string";
}