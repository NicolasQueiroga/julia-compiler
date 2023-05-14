#include "print.hpp"
#include "utils.hpp"
#include "assembler.hpp"
#include <iostream>

Print::Print(std::vector<Node *> children) : children(children)
{
}

ValueType Print::Evaluate()
{
    std::cout << this->children[0]->Evaluate() << std::endl;
    Assembler::incrementAsmCode("PUSH EBX\nCALL print\nPOP EBX");
    return 0;
}