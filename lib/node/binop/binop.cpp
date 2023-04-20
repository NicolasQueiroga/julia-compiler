#include "binop.hpp"

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

int BinOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        this->value = std::get<std::string>(value);
        if (std::get<std::string>(value) == "+")
            return children[0]->Evaluate() + children[1]->Evaluate();
        else if (std::get<std::string>(value) == "-")
            return children[0]->Evaluate() - children[1]->Evaluate();
        else if (std::get<std::string>(value) == "*")
            return children[0]->Evaluate() * children[1]->Evaluate();
        else if (std::get<std::string>(value) == "/")
            return children[0]->Evaluate() / children[1]->Evaluate();
        else if (std::get<std::string>(value) == "||")
            return children[0]->Evaluate() || children[1]->Evaluate();
        else if (std::get<std::string>(value) == "&&")
            return children[0]->Evaluate() && children[1]->Evaluate();
        else if (std::get<std::string>(value) == "<")
            return children[0]->Evaluate() < children[1]->Evaluate();
        else if (std::get<std::string>(value) == ">")
            return children[0]->Evaluate() > children[1]->Evaluate();
        else if (std::get<std::string>(value) == "<=")
            return children[0]->Evaluate() <= children[1]->Evaluate();
        else if (std::get<std::string>(value) == ">=")
            return children[0]->Evaluate() >= children[1]->Evaluate();
        else if (std::get<std::string>(value) == "==")
            return children[0]->Evaluate() == children[1]->Evaluate();
        else if (std::get<std::string>(value) == "!=")
            return children[0]->Evaluate() != children[1]->Evaluate();
        else
            throw "Expected PLUS or MINUS or MUL or DIV or OR or AND";
    }
    else
        throw "Expected string";
}