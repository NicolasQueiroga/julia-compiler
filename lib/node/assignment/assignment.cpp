#include "assignment.hpp"
#include "assembler.hpp"
#include "utils.hpp"
#include <iostream>

Assignment::Assignment(std::vector<Node *> children, std::variant<int, std::string> value) : children(children), value(value)
{
}

ValueType Assignment::Evaluate(SymbolTable *symbolTable)
{
    if (std::holds_alternative<std::string>(value))
    {
        symbolTable->setter(std::get<std::string>(value), children[1]->Evaluate(symbolTable));
        std::string offset = symbolTable->getter(std::get<std::string>(value)).size;
        Assembler::incrementAsmCode("MOV [EBP-" + offset + "], EBX");
    }
    else
        throw "Expected string";
    return 0;
}