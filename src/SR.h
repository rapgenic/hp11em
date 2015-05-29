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

#ifndef STORAGEREGISTER_H
#define	STORAGEREGISTER_H

#include "config.h"

#include <iostream>
using std::cerr;
using std::endl;

#include "colors.h"

class StorageRegister {
public:
    StorageRegister();
    virtual ~StorageRegister();

    bool sr_loc_set(int loc, double numb);
    double sr_loc_get(int loc);

private:
    double sr[21];
};

#endif	/* STORAGEREGISTER_H */

