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

#ifndef AUTOMATICMEMORYSTACK_H
#define AUTOMATICMEMORYSTACK_H

#include "config.h"

#include <cln/cln.h>
using namespace cln;

#include <iostream>
using namespace std;

class AutomaticMemoryStack {
public:
    AutomaticMemoryStack();
    virtual ~AutomaticMemoryStack();

    cl_R get_x();
    cl_R get_y();
    cl_R get_z();
    cl_R get_t();
    cl_R get_lst_x();

    void stack_add(cl_R number);
    void set_x(cl_R num, bool using_lst_x = true);
    void set_y(cl_R num);
    void set_z(cl_R num);
    void set_t(cl_R num);
    void set_lst_x(cl_R num);

    void stack_add(char* num);
    void set_x(char* num, bool using_lst_x = true);
    void set_y(char* num);
    void set_z(char* num);
    void set_t(char* num);
    void set_lst_x(char* num);
private:
    void round_to_limits(cl_R &num);

    cl_R x, y, z, t, lst_x;

    cl_R hlimit, llimit;
    
    cl_read_flags flags;
};

#endif // AUTOMATICMEMORYSTACK_H
