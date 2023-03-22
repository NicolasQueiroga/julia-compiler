#include "assignment.hpp"

Assignment::Assignment(std::vector<Node *> children, std::variant<int, std::string> value) : children(children), value(value)
{
}

int Assignment::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
        this->setter(std::get<1>(value), children[1]->Evaluate());
    else
        throw "Expected string";
    return 0;
}