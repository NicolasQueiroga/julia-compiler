#include "symboltable.hpp"

std::shared_ptr<std::map<std::string, TableValue>> SymbolTable::table = std::make_shared<std::map<std::string, TableValue>>();
int SymbolTable::offset = 0;

SymbolTable::SymbolTable()
{
}

void SymbolTable::create(std::string key, std::string value_type, int type_size, ValueType value)
{
    if (SymbolTable::table->find(key) == SymbolTable::table->end())
    {
        SymbolTable::offset += type_size;
        std::string size = std::to_string(SymbolTable::offset);
        TableValue table_value = {value_type, size, value};
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
        TableValue t = SymbolTable::table->at(key);
        SymbolTable::table->at(key) = {t.value_type, t.size, value};
    }
    else
        throw "Error: " + key + " does not exist.";
}