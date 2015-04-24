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

    cl_R x, y, z, t, lst_x;

    cl_read_flags flags;
};

#endif // AUTOMATICMEMORYSTACK_H
