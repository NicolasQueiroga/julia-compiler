// #define DEBUG

#include <regex>
#include <iostream>
#include "tokenizer.hpp"

Tokenizer::Tokenizer() : next("EOF", 0)
{
    this->reservedWords = std::make_shared<std::vector<std::string>>();
    this->reservedWords->push_back("println");
    this->reservedWords->push_back("readline");
    this->reservedWords->push_back("while");
    this->reservedWords->push_back("if");
    this->reservedWords->push_back("else");
    this->reservedWords->push_back("end");
    this->reservedWords->push_back("Int");
    this->reservedWords->push_back("String");
    this->reservedWords->push_back("function");
    this->reservedWords->push_back("return");
}

void Tokenizer::fetchTokens()
{
    std::smatch m;
    std::regex e("[0-9]+|(_?[a-zA-Z][_a-zA-Z0-9]*_?)|(==)|(!=)|(::)|(\\,)|(>=)|(<=)|(\\|\\|)|(&&)|(\\.)|(\"[^\"]*\")|[\\+\\-\\/\\*\\(\\)\\=\\\n,.<>!?:;@#$%^&*_~`\\|\\{\\}[\\]]");

    while (std::regex_search(this->source, m, e))
    {
        this->tokens.push_back(m[0]);
        this->source = m.suffix();
    }
    this->tokens.push_back("~");

#ifdef DEBUG
    for (std::string token : this->tokens)
        std::cout << token << std::endl;
#endif
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
    else if (tokens[this->position] == "==")
        this->next.type = "EQUALS";
    else if (tokens[this->position] == "!=")
        this->next.type = "NOTEQUALS";
    else if (tokens[this->position] == "!")
        this->next.type = "NOT";
    else if (tokens[this->position] == ">")
        this->next.type = "GREATERTHAN";
    else if (tokens[this->position] == "<")
        this->next.type = "LESSTHAN";
    else if (tokens[this->position] == ">=")
        this->next.type = "GREATERTHANEQUALS";
    else if (tokens[this->position] == "<=")
        this->next.type = "LESSTHANEQUALS";
    else if (tokens[this->position] == "&&")
        this->next.type = "AND";
    else if (tokens[this->position] == "||")
        this->next.type = "OR";
    else if (tokens[this->position] == "\n")
        this->next.type = "NEWLINE";
    else if (tokens[this->position] == "::")
        this->next.type = "DECLARATION";
    else if (tokens[this->position] == ".")
        this->next.type = "CONCAT";
    else if (tokens[this->position] == ".")
        this->next.type = "COMMA";
    else if (std::find(this->reservedWords->begin(), this->reservedWords->end(), tokens[this->position]) != this->reservedWords->end())
    {
        this->next.type = tokens[this->position] == "Int" || tokens[this->position] == "String" ? "TYPE" : tokens[this->position];
        this->next.value = tokens[this->position];
    }
    else if (std::regex_match(tokens[this->position], std::regex("[a-zA-Z0-9_]+")))
    {
        this->next.type = "IDENTIFIER";
        this->next.value = tokens[this->position];
    }
    else if (tokens[this->position].front() == '"' && tokens[this->position].back() == '"')
    {
        this->next.type = "STRING";
        this->next.value = tokens[this->position].substr(1, tokens[this->position].length() - 2);
    }
    else
    {
        this->next.type = "UNKNOWN";
        this->next.value = tokens[this->position];
    }

    this->position++;
}