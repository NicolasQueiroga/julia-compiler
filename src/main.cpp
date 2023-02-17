#include <iostream>
#include <vector>
#include "tokenizer/tokenizer.hpp"

int main(int argc, char **argv)
{
    Tokenizer tokenizer("1 + 2", 0);
    tokenizer.selectNext();
    return 0;
}