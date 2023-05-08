#include "print.hpp"
#include "utils.hpp"
#include <iostream>

Print::Print(std::vector<Node *> children) : children(children)
{
}

ValueType Print::Evaluate()
{
    std::cout << this->children[0]->Evaluate() << std::endl;
    return 0;
}