#include <regex>
#include "tokenizer.hpp"
#include <iostream>

Tokenizer::Tokenizer() : next("EOF", 0)
{
    this->reservedWords = std::make_shared<std::vector<std::string>>();
    this->reservedWords->push_back("println");
}

void Tokenizer::fetchTokens()
{
    std::smatch m;
    std::regex e("[0-9]+|[a-zA-Z]+|[\\+\\-\\/\\*\\(\\)\\=\\\n]");

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
    else if (tokens[this->position] == "*")
        this->next.type = "MULT";
    else if (tokens[this->position] == "/")
        this->next.type = "DIV";
    else if (tokens[this->position] == "(")
        this->next.type = "LPAREN";
    else if (tokens[this->position] == ")")
        this->next.type = "RPAREN";
    else if (tokens[this->position] == "_")
        this->next.type = "EOF";
    else if (tokens[this->position] == "0" || tokens[this->position] == "1" || tokens[this->position] == "2" || tokens[this->position] == "3" || tokens[this->position] == "4" || tokens[this->position] == "5" || tokens[this->position] == "6" || tokens[this->position] == "7" || tokens[this->position] == "8" || tokens[this->position] == "9")
        this->next.type = "NUMBER";
    else
        if (std::find(this->reservedWords->begin(), this->reservedWords->end(), tokens[this->position]) != this->reservedWords->end())
            this->next.type = "RESERVED";

    
    // cout next token
    std::cout << "next token: " << this->next.type << this->next.value << std::endl;

    this->next.type == "NUMBER" ? this->next.value = std::stoi(tokens[this->position]) : int();
    this->position++;
}