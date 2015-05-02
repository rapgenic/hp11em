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

#include <cln/cln.h>
using cln::cl_R;
using cln::cl_read_flags;
using cln::lsyntax_all;
using cln::syntax_real;

#include <iostream>
using std::cerr;
using std::endl;

#include "colors.h"
#include "AMS.h"

AutomaticMemoryStack::AutomaticMemoryStack() {
    lst_x = x = y = z = t = hlimit = "9.999999999L99_10";
    lst_x = x = y = z = t = llimit = "1L-99_10";
    lst_x = x = y = z = t = 0;

#ifdef DEBUG
    cerr << KBLU << "MAX_NUMBER: " << hlimit << KRST << endl;
    cerr << KBLU << "MIN_NUMBER: " << llimit << KRST << endl;
#endif

    flags.lsyntax = lsyntax_all;
    flags.syntax = syntax_real;
    flags.rational_base = 10;
}

AutomaticMemoryStack::~AutomaticMemoryStack() {
}

void AutomaticMemoryStack::stack_add(cl_R number) {
    t = z;
    z = y;
    y = x;
    x = round_to_limits(number);
}

void AutomaticMemoryStack::stack_add(char* num) {
    t = z;
    z = y;
    y = x;
    x = round_to_limits(num);
}

cl_R AutomaticMemoryStack::get_x() {
    return x;
}

cl_R AutomaticMemoryStack::get_y() {
    return y;
}

cl_R AutomaticMemoryStack::get_z() {
    return z;
}

cl_R AutomaticMemoryStack::get_t() {
    return t;
}

cl_R AutomaticMemoryStack::get_lst_x() {
    return lst_x;
}

void AutomaticMemoryStack::set_x(char* num, bool using_lst_x) {
    cl_R cnum = round_to_limits(num);

    if (using_lst_x) {
        lst_x = x;
        x = cnum;
    } else {
        x = cnum;
    }
}

void AutomaticMemoryStack::set_y(char* num) {
    cl_R cnum = round_to_limits(num);
    y = cnum;
}

void AutomaticMemoryStack::set_z(char* num) {
    cl_R cnum = round_to_limits(num);
    z = cnum;
}

void AutomaticMemoryStack::set_t(char* num) {
    cl_R cnum = round_to_limits(num);
    t = cnum;
}

void AutomaticMemoryStack::set_lst_x(char* num) {
    cl_R cnum = round_to_limits(num);
    lst_x = cnum;
}

void AutomaticMemoryStack::set_lst_x(cl_R num) {
    lst_x = round_to_limits(num);;
}

void AutomaticMemoryStack::set_x(cl_R num, bool using_lst_x) {
    num = round_to_limits(num);
    if (using_lst_x) {
        lst_x = x;
        x = num;
    } else {
        x = num;
    }
}

void AutomaticMemoryStack::set_y(cl_R num) {
    y = round_to_limits(num);;
}

void AutomaticMemoryStack::set_z(cl_R num) {
    z = round_to_limits(num);;
}

void AutomaticMemoryStack::set_t(cl_R num) {
    t = round_to_limits(num);;
}

cl_R AutomaticMemoryStack::round_to_limits(cl_R num) {
/*
    if (num > hlimit) {
#ifdef DEBUG
        cerr << KYEL << "NUMBER EXCEEDED MAXIMUM VALUE" << KRST << endl;
#endif
        return hlimit;
    } else if (num < llimit) {
#ifdef DEBUG
        cerr << KYEL << "NUMBER EXCEEDED MINIMUM VALUE" << KRST << endl;
#endif
        return llimit;
    }
*/

#ifdef DEBUG
    cerr << KYEL << "Warning: internal registers limit NOT SUPPORTED YET" << KRST << endl;
#endif     
    return num;
}