#include "parser.hpp"
#include "prepro/prepro.hpp"

Tokenizer Parser::tokenizer = Tokenizer();

int Parser::parseTerm()
{
    int result = 0;
    if (tokenizer.next.type == "NUMBER")
    {
        result = tokenizer.next.value;
        tokenizer.selectNext();
        if (tokenizer.next.type == "NUMBER")
            throw "Expected MULT or DIV";
        while (tokenizer.next.type == "MULT" || tokenizer.next.type == "DIV")
        {
            if (tokenizer.next.type == "MULT")
            {
                tokenizer.selectNext();
                if (tokenizer.next.type == "NUMBER")
                    result *= tokenizer.next.value;
                else
                    throw "Expected NUMBER";
            }
            else if (tokenizer.next.type == "DIV")
            {
                tokenizer.selectNext();
                if (tokenizer.next.type == "NUMBER")
                    result /= tokenizer.next.value;
                else
                    throw "Expected NUMBER";
            }
            tokenizer.selectNext();
            if (tokenizer.next.type == "NUMBER")
                throw "Expected MULT or DIV";
        }
    }
    else
        throw "Expected NUMBER";
    return result;
}

int Parser::parseExpression()
{
    int expResult = 0;
    expResult = Parser::parseTerm();
    while (tokenizer.next.type == "PLUS" || tokenizer.next.type == "MINUS")
    {
        if (tokenizer.next.type == "PLUS")
        {
            tokenizer.selectNext();
            expResult += Parser::parseTerm();
        }
        else if (tokenizer.next.type == "MINUS")
        {
            tokenizer.selectNext();
            expResult -= Parser::parseTerm();
        }
    }

    return expResult;
}

int Parser::run(std::string code)
{
    Prepro::filter(code);
    tokenizer.source = code;
    tokenizer.position = 0;
    tokenizer.fetchTokens();
    tokenizer.next.type != "EOF" ? tokenizer.selectNext() : void(throw "Expected NUMBER");
    return parseExpression();
}