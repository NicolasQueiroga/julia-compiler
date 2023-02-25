#include <iostream>
#include "parser/parser.hpp"

int main(int argc, char **argv)
{
    if (argc > 1)
        std::cout << Parser::run(argv[1]) << '\n';
    return 0;
}