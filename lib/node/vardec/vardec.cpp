#include "vardec.hpp"
#include "assembler.hpp"
#include "utils.hpp"
#include <iostream>

VarDec::VarDec(std::string type, std::string value, std::vector<Node *> children)
    : type(type), value(value), children(children)
{
}

ValueType VarDec::Evaluate(SymbolTable *symbolTable)
{
    Assembler::incrementAsmCode("PUSH DWORD 0");
    int size = this->type == "Int" ? 4 : 1;
    if (this->children[1] != nullptr)
    {
        ValueType eval = this->children[1]->Evaluate(symbolTable);
        symbolTable->create(this->value, this->type, size, eval);
        std::string ofset = symbolTable->getter(this->value).size;
        Assembler::incrementAsmCode("MOV [EBP-" + ofset + "], EBX");
    }
    else
        symbolTable->create(this->value, this->type, size, 0);
    return 0;
}