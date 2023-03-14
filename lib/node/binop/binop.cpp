#include "binop.hpp"

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

BinOp::~BinOp()
{
    // for (Node *child : this->children)
    //     delete child;

    // this->children.clear();
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
        else
            throw "Expected PLUS or MINUS or MUL or DIV";
    }
    else
        throw "Expected string";
}