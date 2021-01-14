//
// Created by cerbe on 02.01.2021.
//

#ifndef BASE12CALC_NUMBER_H
#define BASE12CALC_NUMBER_H

struct Number {
    Number(double number) :
        _number(number) {};

    double getNumber() const {
        return _number;
    }

private:
    double _number;
};

#endif //BASE12CALC_NUMBER_H
