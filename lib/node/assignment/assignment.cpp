#include "assignment.hpp"

Assignment::Assignment(std::vector<Node *> children, std::variant<int, std::string> value) : children(children), value(value)
{
}

ValueType Assignment::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
        this->setter(std::get<std::string>(value), children[1]->Evaluate());
    else
        throw "Expected string";
    return 0;
}