#include "computor.h"

bool validateInput(const std::string& input) {
    // Placeholder for input validation logic
    std::cout << "Validating input: " << input << std::endl;
    try {
        int openParens = 0;

        // Simulate validation
        if (input.empty()) {
            throw std::invalid_argument("Input cannot be empty");
        }
        else if (input.find('=') == std::string::npos) {
            throw std::invalid_argument("Input must contain an equation sign '='");
        }
        else if (input.find_first_not_of("0123456789Xx^*+-= .") != std::string::npos) {
            throw std::invalid_argument("Input contains invalid characters");
        }
        else if (input[0] == '=' || input[0] == '*' || input[0] == '/' || input[0] == '^') {
            throw std::invalid_argument("Input cannot start with '= , * , / , or ^'");
        }
        for (char c : input) {
            if (c == '(') openParens++;
            else if (c == ')') openParens--;
            if (openParens < 0) {
                throw std::invalid_argument("Mismatched parentheses: ')' without '('");
            }
        }
        if (openParens != 0) {
            throw std::invalid_argument("Mismatched parentheses: unclosed '('");
        }
    } catch (const std::exception& e) {
        std::cerr << "Validation error: " << e.what() << std::endl;
        return false;
    }
    return true;
}