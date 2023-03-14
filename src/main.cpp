#include <string>
#include <iostream>
#include <fstream>
#include "parser/parser.hpp"

// #define DEBUG

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::string code = "(((((((1 * 2) + 3) - 4) / 5) + 6) * 7 - 8 + ((9 * 10) / 11 - 12) * 13 + 14 - 15) / 16 + 17 * 18 - 19 + ((20 - 21) * 22 + 23) / 24 * 25 - 26 + ((27 / 28 * 29 - 30) + 31) * 32 - 33 / 34 * 35 + 36 - 37 * 38 / 39 + 40 * 41 / 42 - 43 - 44 / 45 + ((46 - 47) * 48 + 49) / 50 * 51 - 52 / 53 * 54 + ((55 / 56 * 57 - 58) + 59) * 60 - 61 / 62 * 63 + 64 - 65 * 66 / 67 + 68 * 69 / 70 - 71 - 72 / 73 + ((74 - 75) * 76 + 77) / 78 * 79 - 80 / 81 * 82 + ((83 / 84 * 85 - 86) + 87) * 88 - 89 / 90 * 91 + 92 - 93 * 94 / 95 + 96 * 97 / 98 - 99)";
    std::cout << Parser::run(code) << '\n'
              << (((((((1 * 2) + 3) - 4) / 5) + 6) * 7 - 8 + ((9 * 10) / 11 - 12) * 13 + 14 - 15) / 16 + 17 * 18 - 19 + ((20 - 21) * 22 + 23) / 24 * 25 - 26 + ((27 / 28 * 29 - 30) + 31) * 32 - 33 / 34 * 35 + 36 - 37 * 38 / 39 + 40 * 41 / 42 - 43 - 44 / 45 + ((46 - 47) * 48 + 49) / 50 * 51 - 52 / 53 * 54 + ((55 / 56 * 57 - 58) + 59) * 60 - 61 / 62 * 63 + 64 - 65 * 66 / 67 + 68 * 69 / 70 - 71 - 72 / 73 + ((74 - 75) * 76 + 77) / 78 * 79 - 80 / 81 * 82 + ((83 / 84 * 85 - 86) + 87) * 88 - 89 / 90 * 91 + 92 - 93 * 94 / 95 + 96 * 97 / 98 - 99) << '\n';
#else
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

    std::string file_contents((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    std::cout << Parser::run(file_contents) << '\n';

#endif
    return 0;
}