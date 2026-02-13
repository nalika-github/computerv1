#include "computor.h"

namespace {

bool isNumberToken(const std::string& token) {
    static const std::regex numberPattern(R"(^\d+(\.\d+)?$)");
    return std::regex_match(token, numberPattern);
}

bool isOperatorToken(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^" || token == "=";
}

NodePtr makeTokenNode(const std::string& token) {
    if (isNumberToken(token)) {
        return ASTNode::create(NodeType::Term, Term(std::stod(token), 0));
    }
    if (token == "X" || token == "x") {
        return ASTNode::create(NodeType::Variable, std::string("X"));
    }
    if (isOperatorToken(token)) {
        return ASTNode::create(NodeType::Operator, token);
    }
    if (std::isalpha(static_cast<unsigned char>(token[0])) != 0) {
        return ASTNode::create(NodeType::Function, token);
    }
    return ASTNode::create(NodeType::Empty);
}

ASTNodePtr parseSideTokens(const std::string& side) {
    ASTNodePtr sideNode = ASTNode::create(NodeType::Empty);
    std::regex pattern(R"(\d+(?:\.\d+)?|[A-Za-z_]+|[+\-*/^()]|=)");
    std::sregex_iterator it(side.begin(), side.end(), pattern);
    std::sregex_iterator end;

    while (it != end) {
        sideNode->addChild(makeTokenNode(it->str()));
        ++it;
    }
    return sideNode;
}

} // namespace

NodePtr parseTree(const std::string& equation_str)
{
    ASTNodePtr root = ASTNode::create(NodeType::Operator, std::string("="));

    size_t equalPos = equation_str.find('=');
    if (equalPos == std::string::npos) {
        root->addChild(parseSideTokens(equation_str));
        return root;
    }

    std::string left = equation_str.substr(0, equalPos);
    std::string right = equation_str.substr(equalPos + 1);

    root->addChild(parseSideTokens(left));
    root->addChild(parseSideTokens(right));
    return root;
}