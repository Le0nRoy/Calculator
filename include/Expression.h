#pragma once

#include <iostream>
#include <sstream>

struct Expression;

struct Expression {
    void evaluate() const;

    void plus();
    void minus();
    void divide();
    void multiply();

    void addOpenBracket();
    void addClosingBracket();

    void addNumber();

    ~Expression();
};

