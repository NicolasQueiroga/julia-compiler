#pragma once
#include <string>
#include <vector>
#include "token/token.hpp"

class Tokenizer
{
public:
    std::string source;
    int position;
    Token next;
    std::vector<std::string> tokens;

    Tokenizer();
    void fetchTokens();
    void selectNext();
};