#include "token.hpp"

Token::Token(std::string type, int value)
{
    this->type = type;
    this->value = value;
}