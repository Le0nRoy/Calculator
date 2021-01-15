#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

#include "BinaryOperation.h"
#include "Number.h"

struct PriorityComparator {
    bool operator()(const size_t &a, const size_t &b);
};

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

    double getResult() const {return 0;}

    ~Expression() = default;

private:
    enum class Operations : unsigned char{
        OpenBracket,
        CloseBracket,
        AddNumber,
        AddOperator
    };

    // FIXME this can be too big to contain them in class object - refactor them to pointers
    std::string _expression;
    std::vector<double> _numbers;
    std::vector<char> _operators;

    void parseString();

};
