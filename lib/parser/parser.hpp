#pragma once

#include "tokenizer/tokenizer.hpp"
#include "node/node.hpp"

class Parser
{
public:
    static Tokenizer tokenizer;

    static Node *parseBlock();
    static Node *parseStatement();
    static Node *parseExpression();
    static Node *parseTerm();
    static Node *parseFactor();
    static Node *run(std::string code);
};