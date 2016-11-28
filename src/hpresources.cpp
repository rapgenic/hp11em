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

#include "hpresources.h"

int key_status[KEY_NUMBER][3] = {
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {0, S_IDLE, S_IDLE},
  {S_INPUT, S_WAITDATA, S_IDLE},
  {S_INPUT, S_WAITDATA, S_IDLE},
  {S_INPUT, S_WAITDATA, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},

  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, 0, 0},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},

  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {0, S_PREFIX, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},

  {S_IDLE, S_IDLE, S_IDLE},
  {0, 0, 0},
  {0, 0, 0},
  {S_WAITDATA, S_IDLE, S_IDLE},
  {S_WAITDATA, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_INPUT, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},
  {S_IDLE, S_IDLE, S_IDLE},

  {S_IDLE, S_IDLE, S_IDLE},
};

int key_codes[KEY_NUMBER] = {
  GDK_KEY_a,
  GDK_KEY_b,
  GDK_KEY_c,
  GDK_KEY_d,
  GDK_KEY_e,
  GDK_KEY_p,
  GDK_KEY_7,
  GDK_KEY_8,
  GDK_KEY_9,
  GDK_KEY_slash,

  GDK_KEY_q,
  GDK_KEY_w,
  GDK_KEY_s,
  GDK_KEY_o,
  GDK_KEY_t,
  GDK_KEY_x,
  GDK_KEY_4,
  GDK_KEY_5,
  GDK_KEY_6,
  GDK_KEY_asterisk,

  GDK_KEY_r,
  GDK_KEY_g,
  GDK_KEY_u,
  GDK_KEY_y,
  GDK_KEY_BackSpace,
  GDK_KEY_1,
  GDK_KEY_2,
  GDK_KEY_3,
  GDK_KEY_minus,

  GDK_KEY_Escape,
  0,
  0,
  GDK_KEY_h,
  GDK_KEY_l,
  GDK_KEY_0,
  GDK_KEY_period,
  GDK_KEY_z,
  GDK_KEY_plus,

  GDK_KEY_Return
};

int key_location[KEY_NUMBER][4] = {
  { 43, 128, 78, 165},
  { 99, 128, 137, 165},
  { 158, 128, 194, 165},
  { 217, 128, 252, 165},
  { 274, 128, 311, 165},
  { 331, 128, 369, 165},
  { 390, 128, 427, 165},
  { 446, 128, 483, 165},
  { 506, 128, 542, 165},
  { 562, 128, 600, 165},

  { 43, 191, 78, 229},
  { 99, 191, 137, 229},
  { 158, 191, 194, 229},
  { 217, 191, 252, 229},
  { 274, 191, 311, 229},
  { 333, 191, 370, 229},
  { 390, 191, 427, 229},
  { 446, 191, 483, 229},
  { 506, 191, 542, 229},
  { 562, 191, 600, 229},

  { 43, 255, 78, 292},
  { 99, 255, 137, 292},
  { 158, 255, 194, 292},
  { 217, 255, 252, 292},
  { 274, 255, 311, 292},
  { 390, 255, 427, 292},
  { 446, 255, 483, 292},
  { 506, 255, 542, 292},
  { 562, 255, 600, 292},

  { 43, 318, 78, 356},
  { 99, 318, 137, 356},
  { 158, 318, 194, 356},
  { 217, 318, 252, 356},
  { 274, 318, 311, 356},
  { 390, 318, 427, 356},
  { 446, 318, 483, 356},
  { 506, 318, 542, 356},
  { 562, 318, 600, 356},

  { 332, 255, 369, 356}
};

int key_stack_lift_flag[KEY_NUMBER][3] = {
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_NULL, L_TRUE, L_TRUE },
  { L_TRUE, L_NULL, L_NULL },
  { L_TRUE, L_NULL, L_NULL },
  { L_TRUE, L_NULL, L_NULL },
  { L_TRUE, L_TRUE, L_TRUE },

  { L_NULL, L_TRUE, L_NULL },
  { L_NULL, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },

  { L_NULL, L_NULL, L_NULL },
  { L_TRUE, L_NULL, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_NULL, L_TRUE },
  { L_TRUE, L_NULL, L_FALS },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },

  { L_NULL, L_NULL, L_NULL },
  { L_NULL, L_NULL, L_NULL },
  { L_NULL, L_NULL, L_NULL },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_NULL, L_NULL },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_TRUE, L_TRUE, L_TRUE },
  { L_FALS, L_TRUE, L_FALS },
  { L_TRUE, L_TRUE, L_TRUE },

  { L_FALS, L_TRUE, L_TRUE }
};
