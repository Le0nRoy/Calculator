#include <iostream>
#include <string>
#include <memory>

#include "Expression.h"

int main(int argc, char **argv) {
    std::string buf;
    std::shared_ptr<Expression> expression;

    while (true) {
        std::cout << "Please enter your expression:" << std::endl;
        std::getline(std::cin, buf);
        if (buf == "exit") {
            break;
        }

        // FIXME exceptions work badly
        /*
            Please enter your expression:
            1 ++ 2
            Given two operators in sequence.
            1++2
              ^
            1 ++ 2 = 1
         */
        try {
            expression = std::make_shared<Expression>(buf);
            expression->parseExpression();
            std::cout << buf << " = "  << expression->getResult() << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
