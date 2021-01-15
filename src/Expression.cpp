#include "Expression.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <map>
#include <list>

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

void Expression::evaluate() const {

}

void Expression::parseExpression() {
    size_t priority = 0;
    size_t counter = 0;
    // Key is priority, Value - position in _operators
    // FIXME allocate it on heap
    std::map<size_t, size_t, PriorityComparator> priorities;

    // TODO priorities setting may be done with string parsing so merge them
    parseString();

    // Set priorities for operations
    for (auto op : _operators) {
        switch (op) {
            case '(':
                priority += 1000;
                priorities[priority] = counter;
                break;
            case ')':
                // FIXME Here can be caught bug - extra open bracket
                priority -= 1000;
                priorities[priority] = counter;
                break;
            case '*':
            case '/':
                priorities[priority + 100] = counter;
                break;
            case '+':
            case '-':
                priorities[priority] = counter;
                break;
            default:
                // Can't even imagine how to get into this block
                throw ExpressionException("Something gone wrong...");
                break;
        }
        ++priority;
        ++counter;
    }

    // TODO After priorities of operations are set we can finally evaluate our expression using BinaryOperation class

}

void Expression::parseString() {
    size_t i = 0;
    double value;
    std::istringstream iss;
    std::string buf(_expression);
    Operations lastOperation;

    // Remove all spaces due to there uselessness
    // FIXME this may cause bug - if 2 different numbers are separated only by space,
    //  they will be merged into one BIG number
    std::remove(buf.begin(), buf.end(), ' ');
    iss.str(buf);

    _numbers.push_back(NAN);
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
                    _operators.push_back(c);
                    lastOperation = Operations::AddOperator;
                    break;
                case ')':
                    // FIXME NAN should be put BEFORE '(' and AFTER ')'
                    if (lastOperation == Operations::OpenBracket) {
                        throw ExpressionException("Closing bracket goes after opening bracket.");
                    } else if (lastOperation == Operations::AddOperator) {
                        throw ExpressionException("Closing bracket goes after operator.");
                    }
                    _operators.push_back(c);
                    _numbers.push_back(NAN);
                    lastOperation = Operations::CloseBracket;
                    break;
                case '(':
                    // TODO Multiply may be added later
                    if (lastOperation == Operations::AddNumber) {
                        throw ExpressionException("Opening bracket after number (operator should be inserted explicitly).");
                    } else if (lastOperation == Operations::CloseBracket) {
                        throw ExpressionException("Opening bracket after closed bracket (operator should be inserted explicitly).");
                    }
                    _numbers.push_back(NAN);
                    _operators.push_back(c);
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
                        _numbers.push_back(value);
                        lastOperation = Operations::AddNumber;
                    } else {
                        throw ExpressionException("Invalid character is given.");
                    }
                    break;
            }
        }
    } catch (ExpressionException &e) {
        std::string underscoreError(_expression.size(), ' ');
        underscoreError.at(i) = '^';
        std::cout << e.getMessage() << std::endl;
        std::cout << _expression << std::endl;
        std::cout << underscoreError << std::endl;
    } catch (std::exception &e) {
        std::cout << "Unexpected exception was caught parsing expression." << std::endl;
    }
}
