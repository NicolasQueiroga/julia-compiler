#include "parser.hpp"
#include "prepro/prepro.hpp"
#include <iostream>

Tokenizer Parser::tokenizer = Tokenizer();

int Parser::parseFactor()
{
    tokenizer.selectNext();
    if (tokenizer.next.type == "NUMBER")
    {
        int ret = tokenizer.next.value;
        tokenizer.selectNext();
        return ret;
    }
    else if (tokenizer.next.type == "MINUS")
        return -parseFactor();
    else if (tokenizer.next.type == "PLUS")
        return parseFactor();
    else if (tokenizer.next.type == "LPAREN")
    {
        int result = parseExpression();
        if (tokenizer.next.type == "RPAREN")
        {
            tokenizer.selectNext();
            return result;
        }
        else
            throw "Expected RPAREN";
    }
    else
        throw "Expected NUMBER";
}

int Parser::parseTerm()
{
    int expResult = Parser::parseFactor();
    while (tokenizer.next.type == "MULT" || tokenizer.next.type == "DIV")
    {
        if (tokenizer.next.type == "MULT")
            expResult *= Parser::parseFactor();
        else if (tokenizer.next.type == "DIV")
            expResult /= Parser::parseFactor();
    }
    return expResult;
}

int Parser::parseExpression()
{
    int expResult = Parser::parseTerm();
    while (tokenizer.next.type == "PLUS" || tokenizer.next.type == "MINUS")
    {
        if (tokenizer.next.type == "PLUS")
            expResult += Parser::parseTerm();
        else if (tokenizer.next.type == "MINUS")
            expResult -= Parser::parseTerm();
    }
    return expResult;
}

int Parser::run(std::string code)
{
    Prepro::filter(code);
    tokenizer.source = code;
    tokenizer.position = 0;
    tokenizer.fetchTokens();

    int res = parseExpression();
    if (tokenizer.next.type != "EOF")
        throw "Expected EOF";
    return res;
}