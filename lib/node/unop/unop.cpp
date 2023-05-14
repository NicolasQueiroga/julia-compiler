#include "unop.hpp"
#include "assembler.hpp"

UnOp::UnOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType UnOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        int val = std::get<int>(this->children[0]->Evaluate());
        this->value = std::get<std::string>(value);
        if (std::get<std::string>(value) == "+")
            return val;
        else if (std::get<std::string>(value) == "-")
        {
            Assembler::incrementAsmCode("NEG EBX");
            return -val;
        }
        else if (std::get<std::string>(value) == "!")
        {
            Assembler::incrementAsmCode("NOT EBX");
            return !val;
        }
        else
            throw "Expected PLUS or MINUS";
    }
    else
        throw "Expected string";
}