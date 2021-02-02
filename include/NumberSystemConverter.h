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

// 198 D10
// 13a1 D16
struct NumberSystemConverter {
    NumberSystemConverter() = default;

    explicit NumberSystemConverter(const std::string &str)
    : _valueD10(std::nan("")) {
        parseString(str);
    }
    explicit NumberSystemConverter(double valD10) :
            _valueD10(valD10) {};

    void parseString(const std::string& str);

    std::string convert(size_t numberSystem) const;

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
