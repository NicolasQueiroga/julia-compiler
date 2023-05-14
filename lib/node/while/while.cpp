#include "while.hpp"
#include "assembler.hpp"

While::While(std::vector<Node *> children) : children(children) {}

ValueType While::Evaluate()
{
    Assembler::incrementAsmCode("LOOP_" + std::to_string(index) + ":");
    this->children[0]->Evaluate();
    Assembler::incrementAsmCode("CMP EBX, False");
    Assembler::incrementAsmCode("JE EXIT_" + std::to_string(index));
    this->children[1]->Evaluate();
    Assembler::incrementAsmCode("JMP LOOP_" + std::to_string(index));
    Assembler::incrementAsmCode("EXIT_" + std::to_string(index) + ":");
    // while (std::get<int>(this->children[0]->Evaluate()))
    //     this->children[1]->Evaluate();
    return 0;
}