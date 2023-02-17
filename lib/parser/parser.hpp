#pragma once

#include "tokenizer/tokenizer.hpp"

class Parser
{
public:
    static Tokenizer tokenizer;

    Parser();
    static void parseExpression();
    static void run(std::string code);
};