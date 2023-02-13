#pragma once

#include "tokenizer/tokenizer.hpp"

class Parser
{
private:
    static Tokenizer tokenizer;

public:
    Parser();
    static void parseExpression();
    static void run(std::string code);
};