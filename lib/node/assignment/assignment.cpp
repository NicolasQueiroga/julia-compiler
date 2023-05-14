#include "assignment.hpp"
#include "assembler.hpp"
#include "utils.hpp"
#include <iostream>

Assignment::Assignment(std::vector<Node *> children, std::variant<int, std::string> value) : children(children), value(value)
{
}

ValueType Assignment::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        this->setter(std::get<std::string>(value), children[1]->Evaluate());
        std::string ofset = this->getter(std::get<std::string>(value)).size;
        Assembler::incrementAsmCode("MOV [EBP-" + ofset + "], EBX");
    }
    else
        throw "Expected string";
    return 0;
}