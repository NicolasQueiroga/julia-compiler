#pragma once

#include <memory>
#include <map>
#include <string>
#include <variant>

using ValueType = std::variant<int, std::string>;
class SymbolTable
{
protected:
    static std::shared_ptr<std::map<std::string, ValueType>> table;

public:
    SymbolTable();
    ValueType getter(std::string key);
    void setter(std::string key, ValueType value);
};