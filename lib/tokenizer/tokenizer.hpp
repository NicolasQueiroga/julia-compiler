#pragma once

#include <string>
#include "token/token.hpp"

class Tokenizer
{
private:
    std::string source;
    int position;
    Token next;

public:
    Tokenizer();
    void selectNext();
};