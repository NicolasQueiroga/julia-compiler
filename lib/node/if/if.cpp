#include "if.hpp"
#include "assembler.hpp"

If::If(std::vector<Node *> children) : children(children)
{
    this->size = children.size();
}

ValueType If::Evaluate()
{
    this->children[0]->Evaluate();
    Assembler::incrementAsmCode("CMP EBX, True");
    Assembler::incrementAsmCode("JE IF_" + std::to_string(index));
    if (this->size == 3)
        this->children[2]->Evaluate();
    Assembler::incrementAsmCode("JMP EXIT_" + std::to_string(index));
    Assembler::incrementAsmCode("IF_" + std::to_string(index) + ":");
    this->children[1]->Evaluate();
    Assembler::incrementAsmCode("EXIT_" + std::to_string(index) + ":");
    // if (ans)
    //     this->children[1]->Evaluate();
    // else if (this->children[2] != nullptr)
    //     return this->children[2]->Evaluate();
    return 0;
}