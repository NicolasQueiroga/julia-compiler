#include "funcdec.hpp"
#include "utils.hpp"
#include <iostream>

FuncDec::FuncDec(std::string func_type, std::string func_name, std::vector<Node *> params, std::vector<Node *> children) : func_type(func_type), func_name(func_name), params(params), children(children)
{
}

ValueType FuncDec::Evaluate()
{
    return 0;
}
