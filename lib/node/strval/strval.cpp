#include "strval.hpp"
#include <iostream>

StrVal::StrVal(std::vector<Node *> children, ValueType value)
    : children(children), value(value)
{
}

ValueType StrVal::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
        return std::get<std::string>(value);
    else
        throw "Expected string";
}