#include <string>
#include <iostream>
#include <fstream>
#include "parser/parser.hpp"

// #define DEBUG

int main(int argc, char **argv)
{
#ifndef DEBUG
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << '\n';
        return 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile)
    {
        std::cerr << "Error opening file: " << argv[1] << '\n';
        return 1;
    }
#else
    std::ifstream infile("../in/roteiro4.jl");
    if (!infile)
    {
        std::cerr << "Error opening file: ../in/roteiro4.jl\n";
        return 1;
    }
#endif
    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    Node *tree = Parser::run(file_contents);
    tree->Evaluate();
    return 0;
}