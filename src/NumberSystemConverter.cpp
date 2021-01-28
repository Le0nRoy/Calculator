//
// Created by cerbe on 26.01.2021.
//

#include "NumberSystemConverter.h"

NumberSystemConverter::NumberSystemConverter(const std::string &str) :
        _value(std::nan("")) {
    // TODO parse string
    std::istringstream is(str);
    std::string numSysStr;
    std::string numSysNewStr;
    is >> _valueStr >> numSysStr >> numSysNewStr;
    // FIXME check if end of is
    // FIXME check errors of is
    // FIXME here should be exception if smth wrong

    auto parseNumSys = [&is](const std::string& sysStr) -> size_t {
        size_t ret = 0;
        if (sysStr[0] != 'D' && sysStr[0] != 'd') {
            throw std::exception();
        }
        // FIXME reset flags?
        is.str(sysStr);
        is.seekg(1);
        is >> ret;
        // FIXME check that no errors happened and that end of string is reached
        return ret;
    };

    _numSysOrig = parseNumSys(numSysStr);
    _numSysNew = parseNumSys(numSysNewStr);
}

void NumberSystemConverter::convert() {
    // get value from _value
    // convert it
    // write it to _valueStrNew
}

bool NumberSystemConverter::operator==(const NumberSystemConverter &rhs) const {
    // FIXME
    return _numSysOrig == rhs._numSysOrig &&
           _numSysNew == rhs._numSysNew &&
           _value == rhs._value &&
           _valueStrNew == rhs._valueStrNew;
}

bool NumberSystemConverter::operator!=(const NumberSystemConverter &rhs) const {
    return !(rhs == *this);
}

bool NumberSystemConverter::operator<(const NumberSystemConverter &rhs) const {
    // FIXME
    if (_numSysOrig < rhs._numSysOrig)
        return true;
    if (rhs._numSysOrig < _numSysOrig)
        return false;
    if (_numSysNew < rhs._numSysNew)
        return true;
    if (rhs._numSysNew < _numSysNew)
        return false;
    if (_value < rhs._value)
        return true;
    if (rhs._value < _value)
        return false;
    if (_valueStr < rhs._valueStr)
        return true;
    if (rhs._valueStr < _valueStr)
        return false;
    return _valueStrNew < rhs._valueStrNew;
}

bool NumberSystemConverter::operator>(const NumberSystemConverter &rhs) const {
    return rhs < *this;
}

bool NumberSystemConverter::operator<=(const NumberSystemConverter &rhs) const {
    return !(rhs < *this);
}

bool NumberSystemConverter::operator>=(const NumberSystemConverter &rhs) const {
    return !(*this < rhs);
}

size_t NumberSystemConverter::getNumSysOrig() const {
    return _numSysOrig;
}

size_t NumberSystemConverter::getNumSysNew() const {
    return _numSysNew;
}
