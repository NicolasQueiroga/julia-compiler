#include "while.hpp"
#include "assembler.hpp"

While::While(std::vector<Node *> children) : children(children) {}

ValueType While::Evaluate()
{
    while (std::get<int>(this->children[0]->Evaluate()))
        this->children[1]->Evaluate();
    return 0;
}