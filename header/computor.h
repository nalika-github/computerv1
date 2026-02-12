#ifndef COMPUTOR_H
#define COMPUTOR_H

#include "validation.h"
#include "parseTree.h"
#include <iostream>
#include <cmath>
#include <ostream>
#include <regex>
#include <string>
#include <iostream>
#include <stdexcept>

NodePtr parseTree(const std::string& equation);
bool validateInput(const std::string& input);

#endif // COMPUTOR_H