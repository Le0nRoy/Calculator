#pragma once

#include <iostream>
#include <sstream>
#include <list>
#include <utility>

#include "BinaryOperation.h"
#include "Number.h"

struct ExpressionException : std::exception {
    explicit ExpressionException(std::string message) : message(std::move(message)) {}

    const std::string &getMessage() const {
        return message;
    }

private:
    std::string message;
};

struct Expression {
    virtual void evaluate() const;

    explicit Expression(std::string expression) :
        _expression(std::move(expression))
//        bracket_counter(0)
        {
            _numbers.reserve(expression.size() / 2);
            _operators.reserve(expression.size() / 2);
        };

    void parseExpression();

    double getResult();

    ~Expression() = default;

private:
    enum class Operations : unsigned char{
        OpenBracket,
        CloseBracket,
        AddNumber,
        AddOperator
    };

//    size_t bracket_counter;
    // FIXME this can be too big to contain them in class object - refactor them to pointers
    std::string _expression;
    std::vector<double> _numbers;
    std::vector<char> _operators;

    void parseString();
//
//    void addOpenBracket();
//    void addClosingBracket();
//
//    void addOperator(Operators op);
//    void addNumber(Number num);

};
