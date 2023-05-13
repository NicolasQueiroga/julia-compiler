#include "if.hpp"
#include "assembler.hpp"

If::If(std::vector<Node *> children) : children(children)
{
    this->size = children.size();
}

ValueType If::Evaluate()
{
    int ans = std::get<0>(this->children[0]->Evaluate());
    if (ans)
        this->children[1]->Evaluate();
    else if (this->children[2] != nullptr)
        return this->children[2]->Evaluate();
    return 0;
}