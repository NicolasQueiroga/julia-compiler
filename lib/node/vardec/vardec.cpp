#include "vardec.hpp"
#include "assembler.hpp"

VarDec::VarDec(std::string type, std::string value, std::vector<Node *> children)
    : type(type), value(value), children(children)
{
}

ValueType VarDec::Evaluate()
{
    int size = this->type == "Int" ? 4 : 1;
    Assembler::incrementAsmCode("PUSH DWORD 0");
    this->SymbolTable::create(this->value, this->type, size, this->children[1]->Evaluate());
    if (this->children[1] != nullptr)
    {
        std::string ofset = this->getter(this->value).size;
        Assembler::incrementAsmCode("MOV [EBP-" + ofset + "], EBX");
    }
    return 0;
}