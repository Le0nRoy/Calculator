#include <iostream>
#include <string>
#include <memory>

#include "Expression.h"

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
