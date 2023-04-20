#include "if.hpp"

If::If(std::vector<Node *> children) : children(children)
{
    this->size = children.size();
}

int If::Evaluate()
{
    if (this->children[0]->Evaluate())
        this->children[1]->Evaluate();
    else if (this->size == 3)
        return this->children[2]->Evaluate();
    return 0;
}