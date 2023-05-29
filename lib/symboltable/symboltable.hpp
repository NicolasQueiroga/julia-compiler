#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <variant>

using ValueType = std::variant<int, std::string>;
struct TableValue
{
    std::string value_type;
    std::string size;
    ValueType value;
};

class SymbolTable
{
protected:
    std::shared_ptr<std::map<std::string, TableValue>> table;
    static int offset;
    std::vector<std::string> keys;

public:
    SymbolTable();
    void create(std::string key, std::string value_type, int type_size, ValueType value);
    TableValue getter(std::string key);
    void setter(std::string key, ValueType value);
    std::vector<std::string> getKeys();
};