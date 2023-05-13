#include "assembler.hpp"
#include <fstream>
#include <iostream>

std::string Assembler::fileName = "";
std::string Assembler::asmCode = "";

void Assembler::setFileName(std::string file_name)
{
    Assembler::fileName = file_name;
}

void Assembler::setHeader()
{
    std::ifstream infile("include/header.asm");
    if (!infile)
        throw std::runtime_error("Error opening file: include/header.asm\n");
    
    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    Assembler::asmCode += file_contents;
    infile.close();
}

void Assembler::incrementAsmCode(std::string code)
{
    Assembler::asmCode += code;
}

void Assembler::setFooter()
{
    std::ifstream infile("include/footer.asm");
    if (!infile)
        throw std::runtime_error("Error opening file: include/footer.asm\n");
    
    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    Assembler::asmCode += file_contents;
    infile.close();
}

void Assembler::write()
{
    std::string filePath = "../../build/" + fileName + ".asm";
    std::ofstream outfile(filePath);
    outfile << asmCode;
    outfile.close();
}