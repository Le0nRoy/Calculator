//
// Created by cerbe on 02.01.2021.
//

#include "BinaryOperation.h"

BinaryOperation::retType BinaryOperation::evaluate() const {
    if (_left == nullptr || _right == nullptr) {
        throw BinaryOperationException("Not enough numbers given.");
    } else if (_operation == nullptr) {
        throw BinaryOperationException("No operator was given");
    }

    return _operation();
}

void BinaryOperation::addNumber(Number num) {
    if (_left == nullptr) {
        _left = std::make_shared<Number>(num);
    } else if (_right == nullptr) {
        _right = std::make_shared<Number>(num);
    } else {
        throw BinaryOperationException("Too much numbers");
    }
}

void BinaryOperation::addOperator(Operators op) {
    if (_operation == nullptr) {
        switch(op) {
            case Operators::PLUS:
                _operation = std::bind(&BinaryOperation::plus, this);
                break;
            case Operators::MINUS:
                _operation = std::bind(&BinaryOperation::minus, this);
                break;
            case Operators::MUL:
                _operation = std::bind(&BinaryOperation::mul, this);
                break;
            case Operators::DIV:
                _operation = std::bind(&BinaryOperation::div, this);
                break;
            default:
                throw BinaryOperationException("No valid operator was given");
        }
    } else {
        throw BinaryOperationException("More than 1 operator given");
    }
}
