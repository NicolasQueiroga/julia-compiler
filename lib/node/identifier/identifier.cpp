#include "identifier.hpp"

Identifier::Identifier(std::variant<int, std::string> value) : value(value)
{
}

ValueType Identifier::Evaluate()
{
    if (std::holds_alternative<std::string>(value)){
        return this->getter(std::get<std::string>(this->value));}
    else
        throw "Expected string";
}