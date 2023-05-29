#include "symboltable.hpp"
#include <iostream>
#include "utils.hpp"

int SymbolTable::offset = 0;

SymbolTable::SymbolTable()
{
    this->table = std::make_shared<std::map<std::string, TableValue>>();
}

void SymbolTable::create(std::string key, std::string value_type, int type_size, ValueType value)
{
    if (this->table->find(key) == this->table->end())
    {
        if (value_type == "Int" && std::holds_alternative<std::string>(value))
            throw "Error: " + key + " is not an integer.";
        else if (value_type == "String" && std::holds_alternative<int>(value))
            throw "Error: " + key + " is not a string.";

        SymbolTable::offset += type_size;
        std::string size = std::to_string(SymbolTable::offset);
        TableValue table_value = {value_type, size, value};
        this->table->insert({key, table_value});
        this->keys.push_back(key);
    }
    else
        throw "Error: " + key + " already exists.";
}

TableValue SymbolTable::getter(std::string key)
{
    if (this->table->find(key) != this->table->end())
        return this->table->at(key);
    else
        throw "Error: " + key + " does not exist.";
}

void SymbolTable::setter(std::string key, ValueType value)
{
    if (this->table->find(key) != this->table->end())
    {
        TableValue t = this->table->at(key);

        if (t.value_type == "Int" && std::holds_alternative<std::string>(value))
            throw "Error: " + key + " is not an integer.";
        else if (t.value_type == "String" && std::holds_alternative<int>(value))
            throw "Error: " + key + " is not a string.";
            
        this->table->at(key) = {t.value_type, t.size, value};
    }
    else
        throw "Error: " + key + " does not exist.";

}

std::vector<std::string> SymbolTable::getKeys()
{
    return this->keys;
}