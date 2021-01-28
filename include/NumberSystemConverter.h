//
// Created by cerbe on 26.01.2021.
//

#ifndef CALCULATOR_NUMBERSYSTEMCONVERTER_H
#define CALCULATOR_NUMBERSYSTEMCONVERTER_H

#include <string>
#include <utility>
#include <cmath>
#include <sstream>

struct NumberSystemConverterException : std::exception {
    explicit NumberSystemConverterException(std::string message) :
            _message(std::move(message)) {}

    const char *what() const noexcept override {
        return _message.data();
    }

private:
    std::string _message;
};

// TODO allow changing value (create same as constructors method)
// 198 D10 D16
// 13a1 D16 D2
struct NumberSystemConverter {
    explicit NumberSystemConverter(const std::string &str);

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

    size_t getNumSysOrig() const;

    size_t getNumSysNew() const;

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
