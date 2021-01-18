//
// Created by cerbe on 02.01.2021.
//

#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(const Number &left, const Number &right, const char op) :
        _left(std::make_shared<Number>(left)),
        _right(std::make_shared<Number>(right)) {
    switch (op) {
        case '+':
            _operation = std::bind(&BinaryOperation::plus, this);
            break;
        case '-':
            _operation = std::bind(&BinaryOperation::minus, this);
            break;
        case '*':
            _operation = std::bind(&BinaryOperation::mul, this);
            break;
        case '/':
            _operation = std::bind(&BinaryOperation::div, this);
            break;
        default:
            throw BinaryOperationException("No valid operator was given");
    }
}

BinaryOperation::retType BinaryOperation::evaluate() const {
    return _operation();
}

BinaryOperation::retType BinaryOperation::plus() const {
    return _left->getNumber() + _right->getNumber();
}

BinaryOperation::retType BinaryOperation::minus() const {
    return _left->getNumber() - _right->getNumber();
}

BinaryOperation::retType BinaryOperation::mul() const {
    return _left->getNumber() * _right->getNumber();
}

BinaryOperation::retType BinaryOperation::div() const {
    if (_right->getNumber() == 0) {
        throw BinaryOperationException("Zero is given as second operand for division.");
    }
    return _left->getNumber() / _right->getNumber();
}
