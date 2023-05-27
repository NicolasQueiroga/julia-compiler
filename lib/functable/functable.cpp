#include "functable.hpp"

std::shared_ptr<std::map<std::string, Node *>> FuncTable::table = std::make_shared<std::map<std::string, Node *>>();
int FuncTable::offset = 0;

FuncTable::FuncTable()
{
}

void FuncTable::create(std::string key, Node *func_ref, int type_size=0)
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

Node *FuncTable::getter(std::string key)
{
    if (FuncTable::table->find(key) != FuncTable::table->end())
        return FuncTable::table->at(key);
    else
        throw "Error: " + key + " does not exist.";
}
