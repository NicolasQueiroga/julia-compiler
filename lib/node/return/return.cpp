#include "return.hpp"
#include "utils.hpp"
#include "assembler.hpp"
#include <iostream>

Return::Return(std::vector<Node *> children) : children(children)
{
}

ValueType Return::Evaluate()
{
    return this->children[0]->Evaluate();
}