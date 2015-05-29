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

#include "config.h"

#include <iostream>
using std::cerr;
using std::endl;

#include "colors.h"
#include "flags.h"

void Flags::setStackDisabled(bool value) {
    stackDisabled = value;
}

bool Flags::isStackDisabled() const {
    return stackDisabled;
}

void Flags::setPendingData(bool value) {
    pendingData = value;
}

bool Flags::isPendingData() const {
    return pendingData;
}

void Flags::setBase(base_t baseval) {
    base = baseval;
}

Flags::base_t Flags::getBase() const {
    return base;
}

void Flags::setState(state_t st) {
    state = st;
}

Flags::state_t Flags::getState() const {
    return state;
}

void Flags::setNotation(notation_t notat) {
    notation = notat;
#ifdef DEBUG
    cerr << KCYN << "Notation: " << notation << KRST << endl;
#endif
}

Flags::notation_t Flags::getNotation() const {
    return notation;
}

void Flags::setNotPrecision(int figures) {
    notation_precision = figures;
#ifdef DEBUG
    cerr << KCYN << "Notation figures: " << notation_precision << KRST << endl;
#endif
    
    if (notation == N_SCI)
        if (notation_precision > 6)
            notation_precision = 6;
}

int Flags::getNotPrecision() const {
    return notation_precision;
}

