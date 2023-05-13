#include "vardec.hpp"
#include "assembler.hpp"

VarDec::VarDec(std::string type, std::string value, std::vector<Node *> children)
    : type(type), value(value), children(children)
{
}

ValueType VarDec::Evaluate()
{
    this->SymbolTable::create(this->value, this->type, this->children[1]->Evaluate());
    return 0;
}