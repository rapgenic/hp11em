/*
    Copyright (C) 2015 Giulio Girardi.

    This file is part of HP11em.

    HP11em is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HP11em is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HP11em.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "flags.h"

/*bool Flags::isNumberWriting() const {
    return numberWriting;
}

void Flags::setNumberWriting(bool writingNumber) {
    numberWriting = writingNumber;
}

bool Flags::isNumberDecimal() const {
    return numberDecimal;
}

void Flags::setNumberDecimal(bool decimal) {
    numberDecimal = decimal;
}

Flags::DWriteMode_t Flags::getDisplayWMode() const {
    return displayWMode;
}

void Flags::setDisplayWMode(DWriteMode_t dispmode) {
    displayWMode = dispmode;
}

int Flags::getNumberDecCount() const {
    return numberDecCount;
}

void Flags::incNumberDecCount() {
    numberDecCount++;
}

void Flags::resNumberDecimal() {
    numberDecimal = false;
    numberDecCount = 0;
}*/

void Flags::setStackDisabled(bool value) {
    stackDisabled = value;
}

bool Flags::isStackDisabled() const {
    return stackDisabled;
}

void Flags::setBase(base_t baseval) {
    base = baseval;
}

Flags::base_t Flags::getBase() const {
    return base;
}