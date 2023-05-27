#include "funccall.hpp"
#include "utils.hpp"
#include "assembler.hpp"
#include <iostream>

FuncCall::FuncCall(std::string func_name, std::vector<Node *> children) : func_name(func_name), children(children)
{
}

ValueType FuncCall::Evaluate()
{
    return this->children[0]->Evaluate();
}