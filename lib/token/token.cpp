#include "token.hpp"

Token::Token(std::string type, std::variant<int, std::string> value) : type(type), value(value) {}