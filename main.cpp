#include <iostream>
#include <string>
#include <memory>

#include "Expression.h"

/// 1. Test base operations
/// 2. Test simple expressions (with 3-4 expressions)

// 1 + 5 * (421 - 905) / ((390.87 + 60.8) * (9333 - 180.5))
int main(int argc, char **argv) {
    std::string buf;

    while (true) {
        std::cout << "Please enter your expression:" << std::endl;
        std::getline(std::cin, buf);
        std::cout << "You entered:\n" << buf << std::endl;
        if (buf == "exit") {
            break;
        }
        // Should be created on heap not to spend stack memory
//        std::unique_ptr<Expression> pexpr;
//        Expression expr(buf);
//        expr.parseExpression();
    }
    return 0;
}
