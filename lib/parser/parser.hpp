#pragma once
#include "tokenizer/tokenizer.hpp"

class Parser
{
public:
    static Tokenizer tokenizer;

    static int parseExpression();
    static int parseTerm();
    static int run(std::string code);
};