#include "identifier.hpp"
#include "assembler.hpp"

Identifier::Identifier(std::variant<int, std::string> value) : value(value)
{
}

ValueType Identifier::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        TableValue getter = this->getter(std::get<std::string>(this->value));
        if (getter.value_type == "Int")
            return std::get<int>(getter.value);
        else if (getter.value_type == "String")
            return std::get<std::string>(getter.value);
    }
    else
        throw "Expected string";

    return 0;
}