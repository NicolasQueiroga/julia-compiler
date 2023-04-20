#include "while.hpp"

While::While(std::vector<Node *> children) : children(children) {}

int While::Evaluate()
{
    while (this->children[0]->Evaluate())
        this->children[1]->Evaluate();
    return 0;
}