#include "computor.h"

int main(int argc, char* argv[]) {
    NodePtr equation;

    if (argc == 2) {
        std::cout << "Arguments received:" << std::endl;
        if (!validateInput(argv[1])) {
            exit(1);
        }
        equation = parseTree(argv[1]);
        // Euclideanalgorithm(equation);

    } else {
        std::cout << "Please provide exactly one argument." << std::endl;
        std::cout << "input example: ./computorv1 \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
    }
    return 0;
}