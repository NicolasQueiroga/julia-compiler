#include <vector>
#include <ctype.h>
#include <iostream>
#include "tokenizer.hpp"

Tokenizer::Tokenizer(std::string source, int position)
{
    this->source = source + "_";
    this->position = position;
}

void Tokenizer::selectNext()
{
    std::vector<std::string> tokens;
    std::string token;
    
    for (char c : this->source)
    {
        if (c == ' ' || c == '+' || c == '-')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            if (c == '+')
            {
                tokens.push_back("+");
                this->next.type = "PLUS";
            }
            else if (c == '-')
            {
                tokens.push_back("-");
                this->next.type = "MINUS";
            }
            else if (c == '_')
            {
                this->next.type = "EOF";
                break;
            }
        }
        else if (isdigit(c))
            token += c;
    }
    std::cout << "Tokens: ";
    for (std::string token : tokens)
        std::cout << token << " ";
    std::cout << '\n';
}