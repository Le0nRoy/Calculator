//
// Created by cerbe on 26.01.2021.
//

#include "NumberSystemConverter.h"

#include <list>
#include <algorithm>
#include <sstream>

void NumberSystemConverter::parseString(const std::string &str) {
    size_t cnt;
    size_t numSys;
    std::string value;
    std::string numSystemStr;
    std::stringstream is(str);
    is.exceptions(std::istringstream::failbit | std::istringstream::badbit);

    is >> value >> numSystemStr;

    // FIXME this one is unneeded?
    if (is.fail()) {
        throw NumberSystemConverterException("Got error while string parsing");
    }
    if (!is.eof()) {
        std::string errorStr;
        std::string errorPointStr(str.size(), ' ');
        cnt = is.tellg();
        errorPointStr[cnt] = '^';
        is.str(errorStr);
        is << "Got redundant symbols after number system" << std::endl
           << str << std::endl
           << errorPointStr;
        throw NumberSystemConverterException(errorStr);
    }

    if (numSystemStr[0] != 'D' && numSystemStr[0] != 'd') {
        throw NumberSystemConverterException(
                "Number system should be indicated after number with preceding 'D' or 'd' character (e.g. \"D10\")");
    }
    is.str(numSystemStr);
    is.seekg(1);
    is >> numSys;
    // FIXME if (is.fail() || is.bad()) then will be thrown exception
    if (is.fail() || !is.eof()) {
        throw NumberSystemConverterException("Got errors while parsing number system");
    }

    if (numSys == 10) {
        is.str(value);
        is.clear();
        is >> _valueD10;
        // FIXME if (is.fail() || is.bad()) then will be thrown exception
        if (is.fail() || !is.eof()) {
            throw NumberSystemConverterException("Got errors while parsing value");
        }
        return;
    }

    // allowed chars:
    // '0' - '9'
    // 'A' - 'Z'
    // 'a' - 'z'
    cnt = 0;
    _valueD10 = 0;
    for (auto c : value) {
        if (numSys < 10) {
            if (c >= '0' + numSys || c < '0') {
                _valueD10 = std::nan("");
                throw NumberSystemConverterException("Got wrong number or number system");
            }
        } else {
            if ((c < '0' || c > '9') && (c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) {
                _valueD10 = std::nan("");
                throw NumberSystemConverterException("Got wrong number or number system");
            }
        }
        if ((c >= '0' && c <= '9')) {
            _valueD10 += (c - '0') * std::pow(numSys, value.size() - 1 - cnt);
        } else if (c >= 'a' && c <= 'z') {
            _valueD10 += (c - 'a' + 10) * std::pow(numSys, value.size() - 1 - cnt);
        } else {
            _valueD10 += (c - 'A' + 10) * std::pow(numSys, value.size() - 1 - cnt);
        }
        ++cnt;
    }
}

std::string NumberSystemConverter::convert(size_t numberSystem) const {
    if (std::isnan(_valueD10)) {
        throw NumberSystemConverterException("No number to convert to another number system");
    }
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

