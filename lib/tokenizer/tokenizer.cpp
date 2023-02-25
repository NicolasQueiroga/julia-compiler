#include <regex>
#include "tokenizer.hpp"

Tokenizer::Tokenizer() : next("EOF", 0)
{
}

void Tokenizer::fetchTokens()
{
    std::smatch m;
    std::regex e("[0-9]+|[+-]");

    while (std::regex_search(this->source, m, e))
    {
        this->tokens.push_back(m[0]);
        this->source = m.suffix();
    }
    this->tokens.push_back("_");
}

void Tokenizer::selectNext()
{
    if (tokens[this->position] == "+")
        this->next.type = "PLUS";
    else if (tokens[this->position] == "-")
        this->next.type = "MINUS";
    else if (tokens[this->position] == "_")
        this->next.type = "EOF";
    else
        this->next.type = "NUMBER";

    this->next.type == "NUMBER" ? this->next.value = std::stoi(tokens[this->position]) : int();
    this->position++;
}