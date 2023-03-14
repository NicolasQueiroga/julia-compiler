#pragma once

#include "tokenizer/tokenizer.hpp"
#include "node/node.hpp"

class Parser
{
public:
    static Tokenizer tokenizer;

    static Node *parseExpression();
    static Node *parseTerm();
    static Node *parseFactor();
    static int run(std::string code);
};