//
// Created by cerbe on 02.01.2021.
//

#ifndef BASE12CALC_BINARYOPERATION_H
#define BASE12CALC_BINARYOPERATION_H

#include "Number.h"
#include <functional>
#include <memory>
#include <utility>

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

    BinaryOperation(const Number &left, const Number &right, const char op);

private:
    std::shared_ptr<Number> _left = nullptr;
    std::shared_ptr<Number> _right = nullptr;
    std::function<retType()> _operation;

    retType plus() const;

    retType minus() const;

    retType mul() const;

    retType div() const;
};

#endif //BASE12CALC_BINARYOPERATION_H
