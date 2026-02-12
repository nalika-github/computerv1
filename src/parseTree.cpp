#include "parseTree.h"



void tokenization(const std::string& token, NodePtr& equation)
{
    // Placeholder for tokenization logic
    if(token == "+")
    {

    }
}

NodePtr parseTree(const std::string& equation_str)
{
    NodePtr equation = nullptr;
    std::regex pattern(R"([0-9]+|[Xx]|[+\-*/]|=|\(|\)|\^)");
    std::sregex_iterator it(equation_str.begin(), equation_str.end(), pattern);
    std::sregex_iterator end;

    while (it != end) {
        std::cout << "Token: " << it->str() << std::endl;
        tokenization(it->str(), equation);
        ++it;
    }

    std::cout << "Parsing equation: " << equation_str << std::endl;
    // For demonstration, return a nullptr
    return equation;
}