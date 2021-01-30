//
// Created by cerbe on 26.01.2021.
//

#include "NumberSystemConverter.h"

#include <list>
#include <algorithm>
#include <sstream>

void NumberSystemConverter::parseString(const std::string &str) {
    // TODO parse string and convert to D10
    // check if only allowed symbols are present
}

//  firstly translate to D10, than translate to D2
std::string NumberSystemConverter::convert(size_t numberSystem) {
    if (numberSystem == 10) {
        return std::to_string(_valueD10);
    }

    signed char sign = _valueD10 < 0 ? -1 : 1;
    char c;
    size_t fracAccuracy = 10;
    // Integer part of value
    auto valInt = (long long) std::abs(_valueD10);
    // Fractional part of value
    double valFrac = std::abs(_valueD10) - valInt;
    std::string res;
    std::ostringstream ss(res);
    std::list<char> resChars;

    auto getCharNum = [](char val) -> char {
        if (val < 10) {
            return (char) ('0' + val);
        } else {
            return (char) ('A' + (val - 10));
        }
    };

    if (numberSystem < 2 || numberSystem > 36) {
        throw NumberSystemConverterException("Number system should be bigger 1 and smaller 36");
    }
    if (valInt < 10 && valFrac == 0 && numberSystem > 10) {
        return std::to_string(valInt);
    }
    if (valInt < numberSystem && valFrac == 0) {
        return std::string(1, getCharNum(valInt));
    }

    while (valInt > 0) {
        c = getCharNum(static_cast<char>(valInt % numberSystem));
        valInt /= numberSystem;
        resChars.push_front(c);
    }
    if (valFrac != 0) {
        resChars.push_back('.');
        while (--fracAccuracy != 0 || valFrac != 0) {
            valFrac *= numberSystem;
            c = getCharNum(static_cast<char>(valFrac));
            resChars.push_back(c);
        }
    }


    for (auto charVal : resChars) {
        ss << charVal;
    }
    return res;
}

