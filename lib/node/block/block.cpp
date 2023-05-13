#include "block.hpp"
#include "assembler.hpp"

Block::Block(std::vector<Node *> children) : children(children)
{
}

ValueType Block::Evaluate()
{
    for (Node *child : this->children)
        child->Evaluate();
    return 0;
}