#pragma once

#include <memory>
#include <map>
#include <string>

class SymbolTable
{
protected:
    static std::shared_ptr<std::map<std::string, int>> table;

public:
    SymbolTable();
    int getter(std::string key);
    void setter(std::string key, int value);
};