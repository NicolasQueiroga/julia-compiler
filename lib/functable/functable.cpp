#include "functable.hpp"
#include "utils.hpp"
#include <iostream>

std::shared_ptr<std::map<std::string, FuncDec *>> FuncTable::table = std::make_shared<std::map<std::string, FuncDec *>>();
int FuncTable::offset = 0;

FuncTable::FuncTable()
{
}

void FuncTable::create(std::string key, FuncDec *func_ref, int type_size)
{
    if (FuncTable::table->find(key) == FuncTable::table->end())
    {
        FuncTable::offset += type_size;
        std::string size = std::to_string(FuncTable::offset);
        FuncTable::table->insert({key, func_ref});
    }
    else
        throw "Error: " + key + " already exists.";
}

FuncDec *FuncTable::getter(std::string key)
{
    if (FuncTable::table->find(key) != FuncTable::table->end())
    {
        return FuncTable::table->at(key);
    }
    else
        throw "Error: " + key + " does not exist.";
}
