#include "symboltable.hpp"

SymbolTable::SymbolTable()
{
    this->table = std::make_shared<std::map<std::string, int>>();
}

int SymbolTable::getter(std::string key)
{
    return this->table->at(key);
}

void SymbolTable::setter(std::string key, int value)
{
    if (this->table->find(key) != this->table->end())
        this->table->at(key) = value;
    else
        this->table->insert(std::pair<std::string, int>(key, value));
}