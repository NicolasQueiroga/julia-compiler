#include "parser.hpp"

Tokenizer Parser::tokenizer = Tokenizer();

int Parser::parseExpression()
{
    int result = 0;
    if (tokenizer.next.type == "NUMBER")
    {
        result = tokenizer.next.value;
        tokenizer.selectNext();
        if (tokenizer.next.type == "NUMBER")
            throw "Expected PLUS or MINUS";
        while (tokenizer.next.type == "PLUS" || tokenizer.next.type == "MINUS")
        {
            if (tokenizer.next.type == "PLUS")
            {
                tokenizer.selectNext();
                if (tokenizer.next.type == "NUMBER")
                    result += tokenizer.next.value;
                else
                    throw "Expected NUMBER";
            }
            else if (tokenizer.next.type == "MINUS")
            {
                tokenizer.selectNext();
                if (tokenizer.next.type == "NUMBER")
                    result -= tokenizer.next.value;
                else
                    throw "Expected NUMBER";
            }
            tokenizer.selectNext();
            if (tokenizer.next.type == "NUMBER")
                throw "Expected PLUS or MINUS";
        }
    }
    else
        throw "Expected NUMBER";
    return result;
}

int Parser::run(std::string code)
{
    tokenizer.source = code;
    tokenizer.position = 0;
    tokenizer.fetchTokens();
    tokenizer.selectNext();
    return parseExpression();
}