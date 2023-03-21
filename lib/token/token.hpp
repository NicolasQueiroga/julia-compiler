#pragma once
#include <string>
#include <memory>
#include <variant>

class Token
{
public:
    std::string type;
    std::variant<int, std::string> value;

    Token(std::string type, std::variant<int, std::string> value);
};
