#include "unop.hpp"

UnOp::UnOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

UnOp::~UnOp()
{
    // for (Node *child : this->children)
    //     delete child;
    
    // this->children.clear();
}

int UnOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        this->value = std::get<std::string>(value);
        if (std::get<std::string>(value) == "+")
            return this->children[0]->Evaluate();
        else if (std::get<std::string>(value) == "-")
            return -this->children[0]->Evaluate();
        else
            throw "Expected PLUS or MINUS";
    }
    else
        throw "Expected string";
}