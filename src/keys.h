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

#ifndef KEYS_H
#define KEYS_H

#include "config.h"

#define KEY_NUMBER 39

class Keys {
public:
    Keys();
    virtual ~Keys();

    typedef bool key_t;

    typedef enum {
        K_SQR = 0,
        K_EAX,
        K_10X,
        K_YAX,
        K_1DX,
        K_CHS,
        K_NO7,
        K_NO8,
        K_NO9,
        K_DIV,
        K_SST,
        K_GTO,
        K_SIN,
        K_COS,
        K_TAN,
        K_EEX,
        K_NO4,
        K_NO5,
        K_NO6,
        K_PER,
        K_R_S,
        K_GSB,
        K_RDW,
        K_X_Y,
        K_DEL,
        K_NO1,
        K_NO2,
        K_NO3,
        K_MEN,
        K_ONF,
        K_SDF,
        K_GDF,
        K_STO,
        K_RCL,
        K_NO0,
        K_DOT,
        K_SPL,
        K_PIU,
        K_ENT,
    } hp_keycodes;

    const int key_location[KEY_NUMBER][4] = {
        { 43, 135, 78, 165},
        { 99, 135, 137, 165},
        { 158, 135, 194, 165},
        { 217, 135, 252, 165},
        { 274, 135, 311, 165},
        { 331, 135, 369, 165},
        { 390, 135, 427, 165},
        { 446, 135, 483, 165},
        { 506, 135, 542, 165},
        { 562, 135, 600, 165},

        { 43, 195, 78, 229},
        { 99, 195, 137, 229},
        { 158, 195, 194, 229},
        { 217, 195, 252, 229},
        { 274, 195, 311, 229},
        { 333, 195, 370, 229},
        { 390, 195, 427, 229},
        { 446, 195, 483, 229},
        { 506, 195, 542, 229},
        { 562, 195, 600, 229},

        { 43, 260, 78, 293},
        { 99, 260, 137, 293},
        { 158, 260, 194, 293},
        { 217, 260, 252, 293},
        { 274, 260, 311, 293},
        { 390, 260, 427, 293},
        { 446, 260, 483, 293},
        { 506, 260, 542, 293},
        { 562, 260, 600, 293},

        { 43, 323, 78, 356},
        { 99, 323, 137, 356},
        { 158, 323, 194, 356},
        { 217, 323, 252, 356},
        { 274, 323, 311, 356},
        { 390, 323, 427, 356},
        { 446, 323, 483, 356},
        { 506, 323, 542, 356},
        { 562, 323, 600, 356},

        { 332, 262, 369, 356}
    };
};

#endif
