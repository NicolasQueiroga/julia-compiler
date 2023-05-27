#pragma once

#include "node.hpp"

#include <memory>
#include <map>
#include <string>
#include <variant>

using ValueType = std::variant<int, std::string>;
struct FuncTableValue
{
    Node *func_ref;
    std::string loc;
};

class FuncTable
{
protected:
    static std::shared_ptr<std::map<std::string, Node *>> table;
    static int offset;

public:
    FuncTable();
    void create(std::string key, Node *func_ref, int type_size);
    Node *getter(std::string key);
};