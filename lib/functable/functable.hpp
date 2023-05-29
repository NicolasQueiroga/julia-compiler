#pragma once

#include "node.hpp"
#include "funcdec/funcdec.hpp"

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
    static std::shared_ptr<std::map<std::string, FuncDec *>> table;
    static int offset;

public:
    FuncTable();
    void create(std::string key, FuncDec *func_ref, int type_size = 0);
    FuncDec *getter(std::string key);
};