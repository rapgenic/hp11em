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

#include "SR.h"

StorageRegister::StorageRegister() {
    sr_clear();
    _load();
}

StorageRegister::~StorageRegister() {
    _save();
}

void StorageRegister::sr_loc_set(int loc, double numb) {
    sr[loc] = numb;
#ifdef DEBUG
    cerr << KBLU << "STORAGE REGISTER - loc " << loc << " numb " << numb << KRST << endl;
#endif 
}

double StorageRegister::sr_loc_get(int loc) {
    return sr[loc];
}

void StorageRegister::sr_clear() {
    for (int i = 0; i < SR_DIMENSION; i++)
        sr[i] = 0;
}

void StorageRegister::sr_clear_sum() {
    for (int i = 0; i < 6; i++) {
        sr[i] = 0;
    }
}

std::string StorageRegister::getClassName() {
    return SR_CLASSNAME;
}

void StorageRegister::load(std::vector<double> data) {
    return;
}

std::vector<double> StorageRegister::save() {
    std::vector<double> data(SR_DIMENSION);
    
    for (int i = 0; i < SR_DIMENSION; i++) {
        data[i] = sr_loc_get(i);
    }
    
    return data;
}