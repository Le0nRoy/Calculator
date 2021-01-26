//
// Created by cerbe on 26.01.2021.
//

#include "NumberSystemConverter.h"

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
