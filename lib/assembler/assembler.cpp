#include "assembler.hpp"
#include <fstream>
#include <iostream>

std::string Assembler::fileName = "";
std::string Assembler::asmCode = "";

void Assembler::setFileName(std::string file_name)
{
    file_name.erase(file_name.find_last_of("."), std::string::npos);
    Assembler::fileName = file_name;
}

void Assembler::setHeader()
{
    std::ifstream infile("lib/assembler/include/header.asm");
    if (!infile)
        throw std::runtime_error("Error opening file: lib/assembler/include/header.asm\n");
    
    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    Assembler::asmCode += file_contents + '\n';
    infile.close();
}

void Assembler::incrementAsmCode(std::string code)
{
    Assembler::asmCode += '\n' + code;
}

void Assembler::setFooter()
{
    std::ifstream infile("lib/assembler/include/footer.asm");
    if (!infile)
        throw std::runtime_error("Error opening file: lib/assembler/include/footer.asm\n");
    
    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    Assembler::asmCode += "\n\n" + file_contents;
    infile.close();
}

void Assembler::write()
{
    std::string filePath = fileName + ".asm";
    std::ofstream outfile(filePath);
    outfile << asmCode;
    outfile.close();
}