#pragma once

#include <string>

class Assembler
{
private:
    static std::string fileName;
    static std::string asmCode;

public:
    static void setFileName(std::string file_name);
    static void setHeader();
    static void incrementAsmCode(std::string code);
    static void setFooter();
    static void write();
};