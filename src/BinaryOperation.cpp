//
// Created by cerbe on 02.01.2021.
//

#include "BinaryOperation.h"

BinaryOperation::retType BinaryOperation::evaluate() const {
    double res;
    if (_left == nullptr || _right == nullptr) {
        throw BinaryOperationException("Not enough numbers given.");
//        throw std::exception();
    }
    switch(_operator) {
        case Operators::PLUS:
            res = _left->getNumber() + _right->getNumber();
            break;
        case Operators::MINUS:
            res = _left->getNumber() - _right->getNumber();
            break;
        case Operators::MUL:
            res = _left->getNumber() * _right->getNumber();
            break;
        case Operators::DIV:
            res = _left->getNumber() / _right->getNumber();
            break;
        default:
            throw BinaryOperationException("No operator was given");
//            throw std::exception();
            break;
    }
    return res;
}

void BinaryOperation::addNumber(Number num) {
    if (_left == nullptr) {
        _left = new Number(num);
    } else if (_right == nullptr) {
        _right = new Number(num);
    } else {
        throw BinaryOperationException("Too much numbers");
//        throw std::exception();
    }
}

// FIXME change type of _operator to pointer to operation function
void BinaryOperation::addOperator(Operators op) {
    if (_operator == Operators::NO_OP) {
        _operator = op;
    } else {
        throw BinaryOperationException("More than 1 operator given");
//        throw std::exception();
    }
}

BinaryOperation::~BinaryOperation() {
    delete _left;
    delete _right;
}

