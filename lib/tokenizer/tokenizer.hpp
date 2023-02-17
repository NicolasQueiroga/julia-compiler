#pragma once

#include <string>
#include "token/token.hpp"

class Tokenizer
{
public:
    std::string source;
    int position;
    Token next;

    Tokenizer(std::string source, int position);
    void selectNext();
};