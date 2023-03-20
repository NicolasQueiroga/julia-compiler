#include "prepro.hpp"
#include <regex>

void Prepro::filter(std::string &code)
{
    std::regex e("#.*");
    code = std::regex_replace(code, e, "");
}