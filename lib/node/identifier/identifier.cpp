#include "identifier.hpp"
#include "assembler.hpp"
#include "utils.hpp"
#include <iostream>

Identifier::Identifier(std::variant<int, std::string> value) : value(value)
{
}

ValueType Identifier::Evaluate(SymbolTable *symbolTable)
{
    if (std::holds_alternative<std::string>(value))
    {
        TableValue getter = symbolTable->getter(std::get<std::string>(this->value));
        Assembler::incrementAsmCode("MOV EBX, [EBP-" + getter.size + "]");

        return getter.value;
        if (getter.value_type == "Int")
            return std::get<int>(getter.value);
        else if (getter.value_type == "String")
            return std::get<std::string>(getter.value);
    }
    else
        throw "Expected string";

    return 0;
}