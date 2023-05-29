#include "funcdec.hpp"
#include "functable.hpp"
#include "utils.hpp"
#include <iostream>

FuncDec::FuncDec(std::string func_type, std::string func_name, std::vector<Node *> params, std::vector<Node *> children) : func_type(func_type), func_name(func_name), params(params), children(children)
{
}

ValueType FuncDec::Evaluate(SymbolTable *symbolTable)
{
    FuncTable *funcTable = new FuncTable();
    funcTable->create(this->func_name, this);
    delete funcTable;
    return 0;
}

std::vector<Node *> FuncDec::getParams()
{
    return this->params;
}

std::vector<Node *> FuncDec::getChildren()
{
    return this->children;
}

std::string FuncDec::getType()
{
    return this->func_type;
}