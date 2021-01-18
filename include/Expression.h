#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <memory>

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
        _expression(std::make_shared<std::string>(expression))
        {
            _numbers = std::make_shared<_numbers_collection>();
            _operators = std::make_shared<_operators_collection>();
            _numbers->reserve(expression.size() / 2);
            _operators->reserve(expression.size() / 2);
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

    typedef std::vector<double> _numbers_collection;
    typedef std::vector<char> _operators_collection;

    std::shared_ptr<std::string> _expression;
    std::shared_ptr<_numbers_collection> _numbers;
    std::shared_ptr<_operators_collection> _operators;

    void parseString();

};
