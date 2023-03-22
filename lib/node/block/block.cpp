#include "block.hpp"

Block::Block(std::vector<Node *> children) : children(children)
{
}

int Block::Evaluate()
{
    for (Node *child : this->children)
        child->Evaluate();
    return 0;
}