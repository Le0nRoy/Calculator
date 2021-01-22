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

    const char *what() const noexcept override {
        return message.data();
    }

private:
    std::string message;

// TODO add to description of exception more information

//    } catch (ExpressionException &e) {
//        // FIXME _expression may contain spaces - that's why this can't work properly
//        //  std::distance may be used somehow...
////        std::string underscoreError(_expression.size(), ' ');
//        std::string underscoreError(buf.size(), ' ');
//        underscoreError.at(charPositionInBuf) = '^';
//        std::cout << e.getMessage() << std::endl;
////        std::cout << _expression << std::endl;
//        std::cout << buf << std::endl;
//        std::cout << underscoreError << std::endl;
//    }
};

struct Expression {
    explicit Expression(const std::string& expression) :
        _expression(std::make_shared<std::string>(expression))
        {
            _numbers = std::make_shared<_numbers_collection>();
            _operators = std::make_shared<_operators_collection>();
            _numbers->reserve(expression.size() / 2);
            _operators->reserve(expression.size() / 2);
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

    // FIXME later it should be changed to 'Number'
    typedef double _ret_type;
    // FIXME all 'double' should be changed to _ret_type;
    typedef std::vector<double> _numbers_collection;
    typedef std::vector<char> _operators_collection;

    std::shared_ptr<std::string> _expression;
    // FIXME make 'std::tuple' map with number, operator, priority
    std::shared_ptr<_numbers_collection> _numbers;
    std::shared_ptr<_operators_collection> _operators;

    std::shared_ptr<_ret_type> _result;

};
