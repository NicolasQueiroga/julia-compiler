#include "symboltable.hpp"
#include <iostream>

std::shared_ptr<std::map<std::string, ValueType>> SymbolTable::table = std::make_shared<std::map<std::string, ValueType>>();

SymbolTable::SymbolTable()
{
}

ValueType SymbolTable::getter(std::string key)
{
    if (std::holds_alternative<std::string>(SymbolTable::table->at(key)))
        return std::get<std::string>(SymbolTable::table->at(key));
    else if (std::holds_alternative<int>(SymbolTable::table->at(key)))
        return std::get<int>(SymbolTable::table->at(key));
}

void SymbolTable::setter(std::string key, ValueType value)
{
    if (SymbolTable::table->find(key) == SymbolTable::table->end())
        table->insert(std::pair<std::string, ValueType>(key, value));
    else
        table->at(key) = value;
}