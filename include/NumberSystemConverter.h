//
// Created by cerbe on 26.01.2021.
//

#ifndef CALCULATOR_NUMBERSYSTEMCONVERTER_H
#define CALCULATOR_NUMBERSYSTEMCONVERTER_H

#include <string>
#include <utility>
#include <cmath>

struct NumberSystemConverter {
    explicit NumberSystemConverter(std::string str) :
            _valueStr(std::move(str)),
            _value(std::nan("")),
            _numSysNew(0),
            _numSysOrig(0) {
        // TODO parse string
    };

    NumberSystemConverter(double val, size_t original_number_system, size_t new_number_system) :
            _value(val),
            _numSysOrig(original_number_system),
            _numSysNew(new_number_system) {};

    void convert();

    double getValue() const {
        return _value;
    }

    const std::string &getValueStr() const {
        return _valueStr;
    }

    const std::string &getConvertedValue() const {
        return _valueStrNew;
    }

    NumberSystemConverter operator+(const NumberSystemConverter &right);
    NumberSystemConverter operator-(const NumberSystemConverter &right);
    NumberSystemConverter operator*(const NumberSystemConverter &right);
    NumberSystemConverter operator/(const NumberSystemConverter &right);

    NumberSystemConverter operator++();
    NumberSystemConverter operator++(int);
    NumberSystemConverter operator--();
    NumberSystemConverter operator--(int);

    bool operator==(const NumberSystemConverter &rhs) const;

    bool operator!=(const NumberSystemConverter &rhs) const;

    bool operator<(const NumberSystemConverter &rhs) const;

    bool operator>(const NumberSystemConverter &rhs) const;

    bool operator<=(const NumberSystemConverter &rhs) const;

    bool operator>=(const NumberSystemConverter &rhs) const;

private:
    size_t _numSysOrig;
    size_t _numSysNew;
    double _value;
    std::string _valueStr;
    std::string _valueStrNew;
};


#endif //CALCULATOR_NUMBERSYSTEMCONVERTER_H
