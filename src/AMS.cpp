#include "AMS.h"

AutomaticMemoryStack::AutomaticMemoryStack() {
    x = y = z = t = 0;

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
    x = number;
}

void AutomaticMemoryStack::stack_add(char* num) {
    t = z;
    z = y;
    y = x;
    x = num;
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
    //const char* eop;

    cl_R cnum;
    //cnum = read_real(flags, num, NULL, &eop);
    cnum = num;

    if ((cnum / 1000000000) < 10) {
        if (using_lst_x) {
            lst_x = x;
            x = cnum;
        } else {
            x = cnum;
        }
    }
}

void AutomaticMemoryStack::set_y(char* num) {
    //const char* eop;

    cl_R cnum;
    //cnum = read_real(flags, num, NULL, &eop);
    cnum = num;

    if ((cnum / 1000000000) < 10) {
        y = cnum;
    }
}

void AutomaticMemoryStack::set_z(char* num) {
    //const char* eop;

    cl_R cnum;
    //cnum = read_real(flags, num, NULL, &eop);
    cnum = num;

    if ((cnum / 1000000000) < 10) {
        z = cnum;
    }
}

void AutomaticMemoryStack::set_t(char* num) {
    //const char* eop;

    cl_R cnum;
    //cnum = read_real(flags, num, NULL, &eop);
    cnum = num;

    if ((cnum / 1000000000) < 10) {
        t = cnum;
    }
}

void AutomaticMemoryStack::set_lst_x(char* num) {
    //const char* eop;

    cl_R cnum;
    //cnum = read_real(flags, num, NULL, &eop);
    cnum = num;

    if ((cnum / 1000000000) < 10) {
        lst_x = cnum;
    }
}

void AutomaticMemoryStack::set_lst_x(cl_R num) {
    if ((num / 1000000000) < 10)
        lst_x = num;
}

void AutomaticMemoryStack::set_x(cl_R num, bool using_lst_x) {
    if ((num / 1000000000) < 10) {
        if (using_lst_x) {
            lst_x = x;
            x = num;
        } else {
            x = num;
        }
    }
}

void AutomaticMemoryStack::set_y(cl_R num) {
    if ((num / 1000000000) < 10)
        y = num;
}

void AutomaticMemoryStack::set_z(cl_R num) {
    if ((num / 1000000000) < 10)
        z = num;
}

void AutomaticMemoryStack::set_t(cl_R num) {
    if ((num / 1000000000) < 10)
        t = num;
} 