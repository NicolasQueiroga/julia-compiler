#include "symboltable.hpp"
#include <iostream>

std::shared_ptr<std::map<std::string, int>> SymbolTable::table = std::make_shared<std::map<std::string, int>>();

SymbolTable::SymbolTable()
{
}

int SymbolTable::getter(std::string key)
{
    return table->at(key);
}

void SymbolTable::setter(std::string key, int value)
{
    if (SymbolTable::table->find(key) == SymbolTable::table->end())
        table->insert(std::pair<std::string, int>(key, value));
    else
        table->at(key) = value;
}