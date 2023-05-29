#include <string>
#include <iostream>
#include <fstream>
#include "parser/parser.hpp"
#include "symboltable/symboltable.hpp"
#include "assembler/assembler.hpp"

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
    Assembler::setFileName(argv[1]);
#else
    std::ifstream infile("../in/roteiro.jl");
    if (!infile)
    {
        std::cerr << "Error opening file: ../in/roteiro.jl\n";
        return 1;
    }
    Assembler::setFileName("roteiro.jl");
#endif
    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    file_contents += '\n';
    Assembler::setHeader();
    Node *tree = Parser::run(file_contents);
    SymbolTable *st = new SymbolTable();
    tree->Evaluate(st);
    delete tree;
    delete st;
    Assembler::setFooter();
    Assembler::write();
    return 0;
}