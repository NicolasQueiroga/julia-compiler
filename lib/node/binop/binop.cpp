#include "binop.hpp"
#include "assembler.hpp"

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType BinOp::Evaluate()
{
    if (std::holds_alternative<std::string>(value))
    {
        std::string op = std::get<std::string>(value);
        ValueType left = children[0]->Evaluate();
        Assembler::incrementAsmCode("PUSH EBX");
        ValueType right = children[1]->Evaluate();
        Assembler::incrementAsmCode("POP EAX");
        ValueType result = 0;

        if (op == ".")
        {
            if (std::holds_alternative<int>(left))
                left = std::to_string(std::get<int>(left));
            if (std::holds_alternative<int>(right))
                right = std::to_string(std::get<int>(right));
            result = std::get<std::string>(left) + std::get<std::string>(right);
        }
        else if (op == "+")
        {
            Assembler::incrementAsmCode("ADD EAX, EBX");
            if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right))
                result = std::get<std::string>(left) + std::get<std::string>(right);
            else if (std::holds_alternative<int>(left) && std::holds_alternative<std::string>(right))
                result = std::to_string(std::get<int>(left)) + std::get<std::string>(right);
            else if (std::holds_alternative<std::string>(left) && std::holds_alternative<int>(right))
                result = std::get<std::string>(left) + std::to_string(std::get<int>(right));
            else if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                result = std::get<int>(left) + std::get<int>(right);
            else
                throw "Invalid operands for +";
        }
        else
        {
            if (op == "-" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("SUB EAX, EBX");
                result = std::get<int>(left) - std::get<int>(right);
            }
            else if (op == "*" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("IMUL EBX");
                result = std::get<int>(left) * std::get<int>(right);
            }
            else if (op == "/" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("IDIV EBX");
                result = std::get<int>(left) / std::get<int>(right);
            }
            else if (op == "||" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                result = std::get<int>(left) || std::get<int>(right);
            else if (op == "&&" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
                result = std::get<int>(left) && std::get<int>(right);
            else if (op == "<")
                result = left < right;
            else if (op == ">")
                result = left > right;
            else if (op == "<=")
                result = left <= right;
            else if (op == ">=")
                result = left >= right;
            else if (op == "==")
                result = left == right;
            else if (op == "!=")
                result = left != right;
            else
                throw "Expected PLUS or MINUS or MUL or DIV or OR or AND";
        }

        Assembler::incrementAsmCode("MOV EBX, EAX");
        return result;
    }
    else
        throw "Expected string";
}