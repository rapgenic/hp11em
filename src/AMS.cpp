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
    _load();
}

AutomaticMemoryStack::~AutomaticMemoryStack() {
    _save();
}

void AutomaticMemoryStack::stack_add(double number) {
    t = z;
    z = y;
    y = x;
    x = round(number);
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
    lst_x = round(num);
}

void AutomaticMemoryStack::set_x(double num, bool using_lst_x) {
    num = round(num);
    if (using_lst_x) {
        lst_x = x;
        x = num;
    } else {
        x = num;
    }
}

void AutomaticMemoryStack::set_y(double num) {
    y = round(num);
}

void AutomaticMemoryStack::set_z(double num) {
    z = round(num);
}

void AutomaticMemoryStack::set_t(double num) {
    t = round(num);
}

double AutomaticMemoryStack::round(double num) {
    double numb;
    double log10_pnumb = floor(log10(fabs(num)));

    numb = std::round(num * pow10(10)) / pow10(10);

    if (log10_pnumb >= floor(log10(BIGGEST_REPR))) {
        numb = BIGGEST_REPR * (numb >= 0 ? 1 : -1);
    } else if (log10_pnumb <= floor(log10(SMALLST_REPR))) {
        numb = 0;
    }

    return numb;
}

std::string AutomaticMemoryStack::getClassName() {
    return AMS_CLASSNAME;
}

void AutomaticMemoryStack::load(std::vector<double> data) {
    set_x(data[AMS_X_VAL], false);
    set_y(data[AMS_Y_VAL]);
    set_z(data[AMS_Z_VAL]);
    set_t(data[AMS_T_VAL]);
    set_lst_x(data[AMS_LST_X_VAL]);
}

std::vector<double> AutomaticMemoryStack::save() {
    std::vector<double> data(QTY);
    
    data[AMS_X_VAL] = get_x();
    data[AMS_Y_VAL] = get_y();
    data[AMS_Z_VAL] = get_z();
    data[AMS_T_VAL] = get_t();
    data[AMS_LST_X_VAL] = get_lst_x();
    
    return data;
}