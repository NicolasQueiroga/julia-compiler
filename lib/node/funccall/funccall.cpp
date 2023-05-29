#include "funccall.hpp"
#include "funcdec/funcdec.hpp"
#include "utils.hpp"
#include "assembler.hpp"
#include <iostream>

FuncCall::FuncCall(std::string func_name, std::vector<Node *> children) : func_name(func_name), children(children)
{
}

ValueType FuncCall::Evaluate(SymbolTable *symbolTable)
{
    SymbolTable *localSymbolTable = new SymbolTable();

    FuncDec *func = this->FuncTable::getter(this->func_name);
    std::vector<Node *> params = func->getParams();
    for (Node *param : func->getParams())
        param->Evaluate(localSymbolTable);

    std::vector<std::string> keys = localSymbolTable->getKeys();
    for (size_t i = 0; i < this->children.size(); i++)
        localSymbolTable->setter(keys[i], this->children[i]->Evaluate(symbolTable));

    ValueType ret = func->getChildren()[1]->Evaluate(localSymbolTable);
    if ((func->getType() == "Int" && std::holds_alternative<std::string>(ret)) ||
        (func->getType() == "String" && std::holds_alternative<int>(ret)))
        throw std::runtime_error("Type mismatch");
        

    delete localSymbolTable;
    return ret;
}