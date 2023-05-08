#include "symboltable.hpp"
#include <utils.hpp>
#include <iostream>

std::shared_ptr<std::map<std::string, TableValue>> SymbolTable::table = std::make_shared<std::map<std::string, TableValue>>();

SymbolTable::SymbolTable()
{
}

void SymbolTable::showAll()
{
    std::cout << "MAP:\n";
    for (auto const &pair : *SymbolTable::table)
    {
        std::cout << "{" << pair.first << ": " << pair.second.value_type << ", " << pair.second.value << "}" << std::endl;
    }
    std::cout << "END MAP\n";
}

void SymbolTable::create(std::string key, std::string value_type, ValueType value)
{
    if (SymbolTable::table->find(key) == SymbolTable::table->end())
    {
        TableValue table_value = {value_type, value};
        SymbolTable::table->insert({key, table_value});
    }
    else
        throw "Error: " + key + " already exists.";
}

TableValue SymbolTable::getter(std::string key)
{
    if (SymbolTable::table->find(key) != SymbolTable::table->end())
        return SymbolTable::table->at(key);
    else
        throw "Error: " + key + " does not exist.";
}

void SymbolTable::setter(std::string key, ValueType value)
{
    if (SymbolTable::table->find(key) != SymbolTable::table->end())
    {
        std::string type = SymbolTable::table->at(key).value_type;
        SymbolTable::table->at(key) = {type, value};
    }
    else
        throw "Error: " + key + " does not exist.";
}