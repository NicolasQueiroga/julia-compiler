#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

// #define DEBUG

using std::cout;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " <expression>\n";
        return 1;
    }

    
    std::string token;
    std::vector<std::string> tokens;
    std::string expression = argv[1];
    for (char c : expression)
    {
        if (c == '+' || c == '-' || c == ' ')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            if (c != ' ')
                tokens.push_back(std::string(1, c));
        }
        else
            token += c;
    }
    tokens.push_back(token);
    tokens[tokens.size() - 1] == "" ? tokens.pop_back() : void();

#ifdef DEBUG
    for (std::string s : tokens)
        cout << s << "\n";
#endif

    int result = 0;
    bool isNegative = false;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (i % 2 == 0 && (tokens[i] == "+" || tokens[i] == "-"))
        {
            cout << "Invalid expression\n";
            return 1;
        }
        if (i % 2 == 1 && (tokens[i] != "+" && tokens[i] != "-"))
        {
            cout << "Invalid expression\n";
            return 1;
        }
        if (i % 2 != 0)
            isNegative = tokens[i] == "-" ? true : false;
        else
        {
            if (isNegative)
                result -= std::stoi(tokens[i]);
            else
                result += std::stoi(tokens[i]);
        }
    }

    cout << result << "\n";
    return 0;
}