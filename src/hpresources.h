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

#include <gdk/gdkkeysyms.h>

#ifndef HPRESOURCES_H
#define HPRESOURCES_H

#define KEY_NUMBER 39

#define KEY_IS_NUMBER(x) (x == K_NO0 || \
                          x == K_NO1 || \
                          x == K_NO2 || \
                          x == K_NO3 || \
                          x == K_NO4 || \
                          x == K_NO5 || \
                          x == K_NO6 || \
                          x == K_NO7 || \
                          x == K_NO8 || \
                          x == K_NO9)

#define KEY_IS_NEUTRAL(x) (x == K_CHS)

#define KEY_IS_INPUT(x) (KEY_IS_NUMBER(x) || \
                         x == K_EEX || \
                         x == K_DOT)

#define KEY_IS_IDLE(x) (!KEY_IS_INPUT(x) && !KEY_IS_NEUTRAL(x))

/*
 * Typedefs
 */

typedef enum {
        K_SQR = 0,
        K_EAX = 1,
        K_10X = 2,
        K_YAX = 3,
        K_1DX = 4,
        K_CHS = 5,
        K_NO7 = 6,
        K_NO8 = 7,
        K_NO9 = 8,
        K_DIV = 9,

        K_SST = 10,
        K_GTO = 11,
        K_SIN = 12,
        K_COS = 13,
        K_TAN = 14,
        K_EEX = 15,
        K_NO4 = 16,
        K_NO5 = 17,
        K_NO6 = 18,
        K_PER = 19,

        K_R_S = 20,
        K_GSB = 21,
        K_RDW = 22,
        K_X_Y = 23,
        K_DEL = 24,
        K_NO1 = 25,
        K_NO2 = 26,
        K_NO3 = 27,
        K_MEN = 28,

        K_ONF = 29,
        K_SDF = 30,
        K_GDF = 31,
        K_STO = 32,
        K_RCL = 33,
        K_NO0 = 34,
        K_DOT = 35,
        K_SPL = 36,
        K_PIU = 37,

        K_ENT = 38,

        /*
         * These are special keycodes, which aren't mapped to a function
         */
        K_REL = 100
} hp_keycodes_t;

typedef enum {
        S_IDLE = 1,
        S_INPUT = 2,
        S_WAITDATA = 3,
        S_PREFIX = 4,
        S_ERR = 5
} core_states_t;

typedef enum {
        F_NONE = 0,
        F_FKEY = 1,
        F_GKEY = 2
} function_keys_t;

typedef enum {
        M_NONE = 0,
        M_NHYP = 1,
        M_IHYP = 2
} modifiy_keys_t;

typedef enum {
        E_NONE = -1,
        E_IMO = 0,
        E_SRO,
        E_ISO,
        E_IRN,
        E_ILN,
        E_SLD,
        E_IFN,
        E_SER,
        E_PRE
} core_error_t;

typedef enum {
        N_FIX,
        N_SCI,
        N_ENG
} notation_t;

typedef enum {
        T_DEG,
        T_RAD,
        T_GRD
} trig_mode_t;

typedef enum {
        L_NULL = 0,
        L_TRUE,
        L_FALS
} flag_t;

/*
 * Calculator defines
 */

extern int key_status[KEY_NUMBER][3];
extern int key_codes[KEY_NUMBER];
extern int key_location[KEY_NUMBER][4];
extern int key_stack_lift_flag[KEY_NUMBER][3];

#endif /* HPRESOURCES_H */
