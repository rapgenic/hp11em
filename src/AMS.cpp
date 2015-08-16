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

#include "AMS.h"

AutomaticMemoryStack::AutomaticMemoryStack() {
    lst_x = x = y = z = t = 0;
}

AutomaticMemoryStack::~AutomaticMemoryStack() {
}

void AutomaticMemoryStack::stack_add(double number) {
    t = z;
    z = y;
    y = x;
    x = round_to_limits(number);
}

double AutomaticMemoryStack::get_x() {
    return x;
}

double AutomaticMemoryStack::get_y() {
    return y;
}

double AutomaticMemoryStack::get_z() {
    return z;
}

double AutomaticMemoryStack::get_t() {
    return t;
}

double AutomaticMemoryStack::get_lst_x() {
    return lst_x;
}

void AutomaticMemoryStack::set_lst_x(double num) {
    lst_x = round_to_limits(num);
}

void AutomaticMemoryStack::set_x(double num, bool using_lst_x) {
    num = round_to_limits(num);
    if (using_lst_x) {
        lst_x = x;
        x = num;
    } else {
        x = num;
    }
}

void AutomaticMemoryStack::set_y(double num) {
    y = round_to_limits(num);
}

void AutomaticMemoryStack::set_z(double num) {
    z = round_to_limits(num);
}

void AutomaticMemoryStack::set_t(double num) {
    t = round_to_limits(num);
}

double AutomaticMemoryStack::round_to_limits(double num) {
#ifdef DEBUG
    cerr << KYEL << "Warning: internal registers limit NOT SUPPORTED YET" << KRST << endl;
#endif     
    return num;
}