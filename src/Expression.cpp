#include "Expression.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <map>

/// priority / 1000 - get bracket priority (the bigger number - the higher priority)
/// if equals to zero - check other types of priority or equal values
/// (priority % 1000) / 100 - get '*' or '/' priority (the bigger number - the higher priority)
/// if equals to zero - check other types of priority or equal values
/// (priority % 1000) % 100 - get '+' or '-' priority (! the less number - the higher priority)
bool PriorityComparator::operator()(const size_t &a, const size_t &b) {
    size_t comp1 = a;
    size_t comp2 = b;
    if ((comp1 / 1000) > (comp2 / 1000)) {
        return true;
    } else if ((comp1 / 1000) < (comp2 / 1000)) {
        return false;
    }
    comp1 %= 1000;
    comp2 %= 1000;
    if ((comp1 / 100) > (comp2 / 100)) {
        return true;
    } else if ((comp1 / 100) < (comp2 / 100)) {
        return false;
    }
    return (comp1 % 100) < (comp2 % 100);
}

void Expression::parseExpression() {
    // Key is priority, Value - position in _operators
    typedef std::map<size_t, size_t, PriorityComparator> priorities_map;
    // Key is position in _operators, Value - result of operation
    typedef std::map<size_t, double> result_map;
    // Key - value from _numbers, Value - flag showing if number was already used
    typedef std::map<double, bool> used_numbers_map;

    size_t priority = 0;
    size_t operationPosition = 0;
    std::shared_ptr<priorities_map> priorities(new priorities_map);
    std::shared_ptr<result_map> results(new result_map);
    used_numbers_map usedNumbers;

    // TODO priorities setting may be done with string parsing so merge them
    parseString();

    // Set priorities for operations
    for (auto op : *_operators) {
        switch (op) {
            case '(':
                // We don't need brackets to have own priority (they aren't independent operator)
                priority += 1000;
                // priority value will change back to current value in the end of cycle block
                // it is made to prevent bracket of having its own priority in list
                --priority;
                break;
            case ')':
                // FIXME Here can be caught bug - extra closing brackets (or not enough brackets)
                priority -= 1000;
                --priority;
                break;
            case '*':
            case '/':
                (*priorities)[priority + 100] = operationPosition;
                break;
            case '+':
            case '-':
                (*priorities)[priority] = operationPosition;
                break;
            default:
                // Can't even imagine how to get into this block
                throw ExpressionException("Something gone wrong...");
        }
        ++priority;
        ++operationPosition;
    }

    // TODO finalize
    if (priority > 1000 || priority < 0) {
        throw ExpressionException("Got extra brackets");
    }

    for (auto pair : *priorities) {
        double left;
        double right;
        operationPosition = pair.second;
        auto it = results->find(operationPosition - 1);

        if (it == results->end()) {
            left = (*_numbers)[operationPosition];
            if (usedNumbers.find(left) != usedNumbers.end()) {
                left = std::nan("");
            } else {
                usedNumbers[left] = true;
            }
        } else {
            left = it->second;
            results->erase(operationPosition - 1);
        }
        it = results->find(operationPosition + 1);
        if (it == results->end()) {
            right = (*_numbers)[operationPosition + 1];
            if (usedNumbers.find(right) != usedNumbers.end()) {
                right = std::nan("");
            } else {
                usedNumbers[right] = true;
            }
        } else {
            right = it->second;
            results->erase(operationPosition + 1);
        }

        if (std::isnan(left) || std::isnan(right)) {
            if (std::isnan(left)) {
                // Our default value lets us to check if this value is invalid
                size_t nearestDoneOp = _operators->size();
                for (auto res : *results) {
                    if (res.first > operationPosition) {
                        break;
                    }
                    nearestDoneOp = res.first;
                }
                if (nearestDoneOp < _operators->size()) {
                    left = (*results)[nearestDoneOp];
                    results->erase(nearestDoneOp);
                } else {
                    throw ExpressionException("Could not find left operand for operation on position: " + std::to_string(pair.second));
                }
            }
            if (std::isnan(right)) {
                // Our default value lets us to check if this value is invalid
                size_t nearestDoneOp = _operators->size();
                for (auto res : *results) {
                    if (res.first > operationPosition) {
                        nearestDoneOp = res.first;
                        break;
                    }
                }
                if (nearestDoneOp < _operators->size()) {
                    right = (*results)[nearestDoneOp];
                    results->erase(nearestDoneOp);
                } else {
                    throw ExpressionException("Could not find right operand for operation on position: " + std::to_string(pair.second));
                }
            }
        }

        (*results)[operationPosition] = BinaryOperation(Number(left),
                                                        Number(right),
                                                        (*_operators)[operationPosition]).evaluate();
    }

    // After last iteration results should contain only one element
    if (results->size() != 1) {
        throw ExpressionException("More than one result left in map to the last iteration.");
    } else {
        _result = std::make_shared<double>(results->begin()->second);
    }
}

void Expression::parseString() {
    size_t i = 0;
    double value;
    std::istringstream iss;
    std::string buf(*_expression);
    Operations lastOperation;

    // Remove all spaces due to there uselessness
    // FIXME this may cause bug - if 2 different numbers are separated only by space,
    //  they will be merged into one BIG number
    buf.erase(std::remove(buf.begin(), buf.end(), ' '), buf.end());
    iss.str(buf);

    // Parsing string to two separate arrays - _numbers and _operators with next relations:
    // _numbers[i] is LEFT to _operators[i]
    // _numbers[i+1] is RIGHT to _operators[i]
    // if _operators[i] == '(' then _numbers[i] == NAN
    // if _operators[i] == ')' then _numbers[i+1] == NAN
    // if _numbers[i] == NAN it waits for result of operator that put it
    // if _operator[i] == '+' or '-' or '/' or '*'
    //  then _operator[i+1] and _operator[i-1] CAN'T be one of this operators
    // if _operator[i] == '(' then _operator[i+1] CAN'T be '+' or '-' or '/' or '*' or ')'
    try {
        for (i = 0; i < buf.size(); ++i) {
            const char c = buf[i];
            switch (c) {
                case '+':
                case '-':
                case '/':
                case '*':
                    if (lastOperation == Operations::AddOperator) {
                        throw ExpressionException("Given two operators in sequence.");
                    } else if (lastOperation == Operations::OpenBracket) {
                        throw ExpressionException("Operator goes after opening bracket.");
                    }
                    _operators->push_back(c);
                    lastOperation = Operations::AddOperator;
                    break;
                case ')':
                    if (lastOperation == Operations::OpenBracket) {
                        throw ExpressionException("Closing bracket goes after opening bracket.");
                    } else if (lastOperation == Operations::AddOperator) {
                        throw ExpressionException("Closing bracket goes after operator.");
                    }
                    _operators->push_back(c);
                    _numbers->push_back(NAN);
                    lastOperation = Operations::CloseBracket;
                    break;
                case '(':
                    // TODO Multiply may be added later
                    if (lastOperation == Operations::AddNumber) {
                        throw ExpressionException(
                                "Opening bracket after number (operator should be inserted explicitly).");
                    } else if (lastOperation == Operations::CloseBracket) {
                        throw ExpressionException(
                                "Opening bracket after closed bracket (operator should be inserted explicitly).");
                    }
                    _numbers->push_back(NAN);
                    _operators->push_back(c);
                    lastOperation = Operations::OpenBracket;
                    break;
                default:
                    if ((c >= '0' && c <= '9')) {
                        if (lastOperation == Operations::AddNumber) {
                            throw ExpressionException("Given number after another number.");
                        } else if (lastOperation == Operations::CloseBracket) {
                            throw ExpressionException("Given number after closing bracket.");
                        }
                        iss.seekg(i);
                        iss >> value;
                        i = iss.tellg();
                        --i;
                        _numbers->push_back(value);
                        lastOperation = Operations::AddNumber;
                    } else {
                        throw ExpressionException("Invalid character is given.");
                    }
                    break;
            }
        }
    } catch (ExpressionException &e) {
        // FIXME _expression may contain spaces - that's why this can't work properly
        //  std::distance may be used somehow...
//        std::string underscoreError(_expression.size(), ' ');
        std::string underscoreError(buf.size(), ' ');
        underscoreError.at(i) = '^';
        std::cout << e.getMessage() << std::endl;
//        std::cout << _expression << std::endl;
        std::cout << buf << std::endl;
        std::cout << underscoreError << std::endl;
    } catch (std::exception &e) {
        std::cout << "Unexpected exception was caught parsing expression." << std::endl;
    }
}

double Expression::getResult() {
    if (_result == nullptr) {
        this->parseExpression();
    }
    return *_result;
}
