#include "if.hpp"
#include "assembler.hpp"

If::If(std::vector<Node *> children) : children(children)
{
    this->size = children.size();
}

ValueType If::Evaluate(SymbolTable *symbolTable)
{
    // this->children[0]->Evaluate(symbolTable);
    // Assembler::incrementAsmCode("CMP EBX, True");
    // Assembler::incrementAsmCode("JE IF_" + std::to_string(index));
    // if (this->children[2] != nullptr)
    //     this->children[2]->Evaluate(symbolTable);
    // Assembler::incrementAsmCode("JMP EXIT_" + std::to_string(index));
    // Assembler::incrementAsmCode("IF_" + std::to_string(index) + ":");
    // this->children[1]->Evaluate(symbolTable);
    // Assembler::incrementAsmCode("EXIT_" + std::to_string(index) + ":");
    int ans = std::get<0>(this->children[0]->Evaluate(symbolTable));
    if (ans)
        this->children[1]->Evaluate(symbolTable);
    else if (this->children[2] != nullptr)
        return this->children[2]->Evaluate(symbolTable);
    return 0;
}