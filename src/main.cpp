#include <iostream>
#include "parser/parser.hpp"

int main(int argc, char **argv)
{
    std::cout << Parser::run("1-2") << '\n';
    return 0;
}