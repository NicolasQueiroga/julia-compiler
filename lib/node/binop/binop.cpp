#include "binop.hpp"
#include "assembler.hpp"

BinOp::BinOp(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType BinOp::Evaluate(SymbolTable *symbolTable)
{
    if (std::holds_alternative<std::string>(value))
    {
        std::string op = std::get<std::string>(value);
        ValueType left = children[0]->Evaluate(symbolTable);
        Assembler::incrementAsmCode("PUSH EBX");
        ValueType right = children[1]->Evaluate(symbolTable);
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
            Assembler::incrementAsmCode("MOV EBX, EAX");
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
                Assembler::incrementAsmCode("MOV EBX, EAX");
                result = std::get<int>(left) - std::get<int>(right);
            }
            else if (op == "*" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("IMUL EBX");
                Assembler::incrementAsmCode("MOV EBX, EAX");
                result = std::get<int>(left) * std::get<int>(right);
            }
            else if (op == "/" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("IDIV EBX");
                Assembler::incrementAsmCode("MOV EBX, EAX");
                result = std::get<int>(left) / std::get<int>(right);
            }
            else if (op == "||" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("OR EAX, EBX");
                Assembler::incrementAsmCode("MOV EBX, EAX");
                result = std::get<int>(left) || std::get<int>(right);
            }
            else if (op == "&&" && std::holds_alternative<int>(left) && std::holds_alternative<int>(right))
            {
                Assembler::incrementAsmCode("AND EAX, EBX");
                Assembler::incrementAsmCode("MOV EBX, EAX");
                result = std::get<int>(left) && std::get<int>(right);
            }
            else if (op == "<")
            {
                Assembler::incrementAsmCode("CMP EAX, EBX");
                Assembler::incrementAsmCode("CALL binop_jl");
                result = left < right;
            }
            else if (op == ">")
            {
                Assembler::incrementAsmCode("CMP EAX, EBX");
                Assembler::incrementAsmCode("CALL binop_jg");
                result = left > right;
            }
            else if (op == "<=")
                result = left <= right;
            else if (op == ">=")
                result = left >= right;
            else if (op == "==")
            {
                Assembler::incrementAsmCode("CMP EAX, EBX");
                Assembler::incrementAsmCode("CALL binop_je");
                result = left == right;
            }
            else if (op == "!=")
                result = left != right;
            else
                throw "Expected PLUS or MINUS or MUL or DIV or OR or AND";
        }

        return result;
    }
    else
        throw "Expected string";
}