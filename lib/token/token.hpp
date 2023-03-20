#pragma once
#include <string>
#include <memory>

class Token
{
public:
    std::string type;
    int value;

    Token(std::string type, int value);
};
