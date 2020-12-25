#include <iostream>
#include <string>
#include <algorithm>

#include "Expression.h"

// 1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))
int main(int argc, char **argv) {
    double value;
    std::string buf;
    std::istringstream iss;
    Expression expr;

    while (true) {
        std::cout << "Please enter your expression:" << std::endl;
        std::getline(std::cin, buf);
        std::cout << "You entered:\n" << buf << std::endl;
        if (buf == "exit") {
            break;
        }

        // ## Parse string
        // # Remove all spaces due to there uselessness
        std::remove(buf.begin(), buf.end(), ' ');
        iss.str(buf);

        for (size_t i = 0; i < buf.size(); ++i) {
            const char c = buf[i];
            switch (c) {
                case '(':
                    expr.addOpenBracket();
                    break;
                case ')':
                    expr.addClosingBracket();
                    break;
                case '+':
                    expr.plus();
                    break;
                case '-':
                    expr.minus();
                    break;
                case '/':
                    expr.divide();
                    break;
                case '*':
                    expr.multiply();
                    break;
                default:
                    // to all cases should be added:
                    // 1. TODO check for empty string - one operator goes after another - bad
                    // 2. TODO value parser should throw exception if more than one dot is present
                    if ((c >= '0' && c <= '9') || c == '.') {
                        iss.seekg(i);
                        iss >> value;
                        i = iss.tellg();
                        --i;
                    }
                    break;
            }
        }
//		expr = new BinaryOperation(buf);
    }
    return 0;
}
