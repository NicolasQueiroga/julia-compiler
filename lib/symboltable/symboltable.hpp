#pragma once

#include <memory>
#include <map>
#include <string>
#include <variant>

using ValueType = std::variant<int, std::string>;
struct TableValue
{
    std::string value_type;
    ValueType value;
};

class SymbolTable
{
protected:
    static std::shared_ptr<std::map<std::string, TableValue>> table;

public:
    SymbolTable();
    void create(std::string key, std::string value_type, ValueType value);
    TableValue getter(std::string key);
    void setter(std::string key, ValueType value);

    void showAll();
};