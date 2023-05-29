#include "intval.hpp"
#include "assembler.hpp"

IntVal::IntVal(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType IntVal::Evaluate(SymbolTable *symbolTable)
{
    if (std::holds_alternative<int>(value))
    {
        Assembler::incrementAsmCode("MOV EBX, " + std::to_string(std::get<int>(value)));
        return std::get<int>(value);
    }
    else
        throw "Expected int";
}