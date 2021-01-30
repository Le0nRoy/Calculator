//
// Created by cerbe on 26.01.2021.
//

#ifndef CALCULATOR_NUMBERSYSTEMCONVERTER_H
#define CALCULATOR_NUMBERSYSTEMCONVERTER_H

#include <string>
#include <utility>
#include <cmath>

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
    NumberSystemConverter() = default;

    explicit NumberSystemConverter(const std::string &str) {
        parseString(str);
    }
    explicit NumberSystemConverter(double val) :
            _valueD10(val) {};

    void parseString(const std::string& str);

    std::string convert(size_t numberSystem);

    double getValueD10() const {
        return _valueD10;
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
    double _valueD10;
};


#endif //CALCULATOR_NUMBERSYSTEMCONVERTER_H
