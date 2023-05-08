#include "intval.hpp"

IntVal::IntVal(std::vector<Node *> children, std::variant<int, std::string> value)
    : children(children), value(value)
{
}

ValueType IntVal::Evaluate()
{
    if (std::holds_alternative<int>(value))
        return std::get<int>(value);
    else
        throw "Expected int";
}