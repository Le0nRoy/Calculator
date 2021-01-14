//
// Created by cerbe on 02.01.2021.
//

#ifndef BASE12CALC_BINARYOPERATION_H
#define BASE12CALC_BINARYOPERATION_H

#include "Number.h"
#include <functional>
#include <utility>

enum class Operators {
    NO_OP, // No operator - default value
    MUL,
    DIV,
    PLUS,
    MINUS
};

struct BinaryOperationException : std::exception {
    BinaryOperationException(std::string message) : message(std::move(message)) {}

    const std::string &getMessage() const {
        return message;
    }

private:
    std::string message;
};

struct BinaryOperation {
    // FIXME return value should be Number, not double
    typedef double retType;

    retType evaluate() const;

    virtual ~BinaryOperation();

    void addNumber(Number num);

    void addOperator(Operators op);

private:
    Number *_left = nullptr;
    Number *_right = nullptr;
    Operators _operator = Operators::NO_OP;
    std::function<retType(const Number &, const Number &)> _operation;

    retType plus(const Number &left, const Number &right) {
        return left.getNumber() + right.getNumber();
    }
    retType minus(const Number &left, const Number &right) {
        return left.getNumber() - right.getNumber();
    }
    retType mul(const Number &left, const Number &right) {
        return left.getNumber() * right.getNumber();
    }
    retType div(const Number &left, const Number &right) {
        return left.getNumber() / right.getNumber();
    }
};

#endif //BASE12CALC_BINARYOPERATION_H
