#pragma once
#include <string>

class Token
{
public:
    std::string type;
    int value;

    Token(std::string type, int value);
};
