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
    // optimized:
    std::shared_ptr<std::vector<std::string>> reservedWords;

    Tokenizer();
    void fetchTokens();
    void selectNext();
};