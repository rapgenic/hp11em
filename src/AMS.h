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

#include <iostream>
using std::cerr;
using std::endl;

#include "colors.h"

class AutomaticMemoryStack {
public:
    AutomaticMemoryStack();
    virtual ~AutomaticMemoryStack();

    double get_x();
    double get_y();
    double get_z();
    double get_t();
    double get_lst_x();

    void stack_add(double number);
    void set_x(double num, bool using_lst_x = true);
    void set_y(double num);
    void set_z(double num);
    void set_t(double num);
    void set_lst_x(double num);

    /*  void stack_add(char* num);
      void set_x(char* num, bool using_lst_x = true);
      void set_y(char* num);
      void set_z(char* num);
      void set_t(char* num);
      void set_lst_x(char* num);*/
private:
    double round_to_limits(double num);

    double x, y, z, t, lst_x;
};

#endif // AUTOMATICMEMORYSTACK_H
