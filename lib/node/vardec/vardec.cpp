#include "vardec.hpp"
#include "assembler.hpp"

VarDec::VarDec(std::string type, std::string value, std::vector<Node *> children)
    : type(type), value(value), children(children)
{
}

ValueType VarDec::Evaluate()
{
    Assembler::incrementAsmCode("PUSH DWORD 0");
    int size = this->type == "Int" ? 4 : 1;
    if (this->children[1] != nullptr)
    {
        int eval = std::get<int>(this->children[1]->Evaluate());
        this->SymbolTable::create(this->value, this->type, size, eval);
        std::string ofset = this->getter(this->value).size;
        Assembler::incrementAsmCode("MOV [EBP-" + ofset + "], EBX");
    }
    else
        this->SymbolTable::create(this->value, this->type, size, 0);
    return 0;
}