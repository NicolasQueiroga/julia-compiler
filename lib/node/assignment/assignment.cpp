#include "assignment.hpp"
#include <iostream>
#include <variant>

Assignment::Assignment(std::vector<Node *> children, std::variant<int, std::string> value) : children(children), value(value)
{
}

int Assignment::Evaluate()
{
    std::string name = std::get<std::string>(this->children[0]->value);
    int val = this->children[1]->Evaluate();
    std::cout << "Assigning " << val << " to " << (std::get<std::string>(this->children[0]->value)) << std::endl;
    this->setter(name, val);
    throw "Not implemented";
    return 0;
}