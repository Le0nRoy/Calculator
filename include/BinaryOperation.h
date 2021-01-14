//
// Created by cerbe on 02.01.2021.
//

#ifndef BASE12CALC_BINARYOPERATION_H
#define BASE12CALC_BINARYOPERATION_H

#include "Number.h"
#include <functional>
#include <utility>

enum class Operators {
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

    // TODO derieve class from interface Operation
    virtual ~BinaryOperation();

    void addNumber(Number num);

    void addOperator(Operators op);

private:
    Number *_left = nullptr;
    Number *_right = nullptr;
    std::function<retType ()> _operation;

    retType plus() const {
        return _left->getNumber() + _right->getNumber();
    }
    retType minus() const {
        return _left->getNumber() - _right->getNumber();
    }
    retType mul() const {
        return _left->getNumber() * _right->getNumber();
    }
    retType div() const {
        if (_right->getNumber() == 0) {
            throw BinaryOperationException("Zero is given as second operand for division.");
        }
        return _left->getNumber() / _right->getNumber();
    }
};

#endif //BASE12CALC_BINARYOPERATION_H
