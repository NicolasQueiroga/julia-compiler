#include <regex>
#include "tokenizer.hpp"

Tokenizer::Tokenizer() : next("EOF", 0)
{
    this->reservedWords = std::make_shared<std::vector<std::string>>();
    this->reservedWords->push_back("println");
}

void Tokenizer::fetchTokens()
{
    std::smatch m;
    std::regex e("[a-zA-Z_][a-zA-Z0-9_]*|[-+*/()={}\\[\\],.<>!?:;@#$%^&*_~`\\|]+|[0-9]+|\\n");

    while (std::regex_search(this->source, m, e))
    {
        this->tokens.push_back(m[0]);
        this->source = m.suffix();
    }
    this->tokens.push_back("~");
}

void Tokenizer::selectNext()
{
    bool is_number = true;
    for (char c : tokens[this->position])
        if (!isdigit(c))
            is_number = false;

    if (is_number)
    {
        this->next.type = "NUMBER";
        this->next.value = std::stoi(tokens[this->position]);
    }
    else if (tokens[this->position] == "+")
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
    else if (tokens[this->position] == "~")
        this->next.type = "EOF";
    else if (tokens[this->position] == "=")
        this->next.type = "ASSIGN";
    else if (tokens[this->position] == "\n")
        this->next.type = "NEWLINE";
    else if (std::find(this->reservedWords->begin(), this->reservedWords->end(), tokens[this->position]) != this->reservedWords->end())
        this->next.type = "RESERVED";
    else if (std::regex_match(tokens[this->position], std::regex("[a-zA-Z0-9_]+")))
    {
        this->next.type = "IDENTIFIER";
        this->next.value = tokens[this->position];
    }
    else
    {
        this->next.type = "UNKNOWN";
        this->next.value = tokens[this->position];
    }

    this->position++;
}