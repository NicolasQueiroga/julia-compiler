#include "block.hpp"
#include "assembler.hpp"
#include "return/return.hpp"
#include <typeinfo>

Block::Block(std::vector<Node *> children) : children(children)
{
}

ValueType Block::Evaluate(SymbolTable *symbolTable)
{
    for (Node *child : this->children)
    {
        if (typeid(*child) == typeid(Return))
            return child->Evaluate(symbolTable);
        child->Evaluate(symbolTable);
    }
    return 0;
}