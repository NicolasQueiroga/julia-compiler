#include "print.hpp"
#include "utils.hpp"
#include "assembler.hpp"
#include <iostream>

Print::Print(std::vector<Node *> children) : children(children)
{
}

ValueType Print::Evaluate(SymbolTable *symbolTable)
{
    std::cout << this->children[0]->Evaluate(symbolTable) << std::endl;
    // this->children[0]->Evaluate(symbolTable);
    // Assembler::incrementAsmCode("PUSH EBX\nCALL print\nPOP EBX");
    return 0;
}