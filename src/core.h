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

#ifndef CORE_H
#define CORE_H

#include "config.h"

#include <iostream>
using namespace std;

#include "keys.h"
#include "signals.h"
#include "dispdrawarea.h"
#include "displaymodule.h"
#include "AMS.h"
#include "flags.h"

class Core : public sigc::trackable {
public:
    Core(Signals *hpsignals_r);
    virtual ~Core();

    void keyPressEvent(int key);

    typedef struct {
        char str[100];
        // | Example: str = "+123,123.00"; global position == 11
        // V number position == 6
        int cursor;     // global position of the string
        int n_cursor;   // Number position of the string (eg the number of the digits)
    } display_temp;

    typedef enum {
        S_NUL = -1,
        S_FIX = 0,
        S_SOF,
        S_GOF
    } pending_states;

    typedef enum {
        F_NULL = 0,
        F_FKEY,
        F_GKEY
    } function_states;

    typedef enum {
        O_ADD = 0,
        O_SUB,
        O_MLT,
        O_DIV
    } operators;

private:
    Signals *hpSignals;
    AutomaticMemoryStack hpAMS;
    DisplayModule hpDisplay;
    Flags hpFlags;
    display_temp hpTempDisp;

    unsigned char function_keys;

    int f_key_set(unsigned char value);
    int f_key_toggle(int key);

    void kcb_sqrt();
    void kcb_alpha_a();
    void kcb_x_2();

    void kcb_e_x();
    void kcb_alpha_b();
    void kcb_ln();

    void kcb_10_x();
    void kcb_alpha_c();
    void kcb_log();

    void kcb_y_x();
    void kcb_alpha_d();
    void kcb_percent();

    void kcb_1_x();
    void kcb_alpha_e();
    void kcb_d_percent();

    void kcb_chs();
    void kcb_pi();
    void kcb_abs();

    void kcb_7();
    void kcb_fix();
    void kcb_deg();

    void kcb_8();
    void kcb_sci();
    void kcb_rad();

    void kcb_9();
    void kcb_eng();
    void kcb_grd();

    void kcb_div();
    void kcb_x_mineq_y();
    void kcb_x_min_0();

    void kcb_sst();
    void kcb_lbl();
    void kcb_bst();

    void kcb_gto();
    void kcb_hyp();
    void kcb_hyp_neg_1();

    void kcb_sin();
    void kcb_x_xcng_i();
    void kcb_sin_neg_1();

    void kcb_cos();
    void kcb_i();
    void kcb_cos_neg_1();

    void kcb_tan();
    void kcb_I();
    void kcb_tan_neg_1();

    void kcb_eex();
    void kcb_to_r();
    void kcb_to_p();

    void kcb_4();
    void kcb_x_xcng_I();
    void kcb_sf();

    void kcb_5();
    void kcb_dse();
    void kcb_cf();

    void kcb_6();
    void kcb_isg();
    void kcb_f_();

    void kcb_per();
    void kcb_x_maj_y();
    void kcb_x_maj_0();

    void kcb_r_s();
    void kcb_pse();
    void kcb_p_r();

    void kcb_gsb();
    void kcb_sum();
    void kcb_rtn();

    void kcb_r_dwn();
    void kcb_prgm();
    void kcb_r_up();

    void kcb_x_xcng_y();
    void kcb_reg();
    void kcb_rnd();

    void kcb_del();
    void kcb_prefix();
    void kcb_clx();

    void kcb_1();
    void kcb_p_y_x();
    void kcb_c_y_x();

    void kcb_2();
    void kcb_to_hms();
    void kcb_to_h();

    void kcb_3();
    void kcb_to_rad();
    void kcb_to_deg();

    void kcb_min();
    void kcb_x_div_y();
    void kcb_x_div_0();

    void kcb_off();

    void kcb_sto();
    void kcb_frac();
    void kcb_int();

    void kcb_rcl();
    void kcb_user();
    void kcb_mem();

    void kcb_0();
    void kcb_x_();
    void kcb_avg_x();

    void kcb_dot();
    void kcb_y_r();
    void kcb_s();

    void kcb_sum_plus();
    void kcb_l_r();
    void kcb_sum_minus();

    void kcb_plus();
    void kcb_x_eq_y();
    void kcb_x_eq_0();

    void kcb_enter();
    void kcb_ran();
    void kcb_lst_x();

    //COMMON FUNCTIONS
    void kcb_c_number(int n);
    void kcb_c_stdopr(operators op);
    void reset_number();

    void (Core::*keys_cb[KEY_NUMBER][3])(void) = {
        {&Core::kcb_sqrt, &Core::kcb_alpha_a, &Core::kcb_x_2},
        {&Core::kcb_e_x, &Core::kcb_alpha_b, &Core::kcb_ln},
        {&Core::kcb_10_x, &Core::kcb_alpha_c, &Core::kcb_log},
        {&Core::kcb_y_x, &Core::kcb_alpha_d, &Core::kcb_percent},
        {&Core::kcb_1_x, &Core::kcb_alpha_e, &Core::kcb_d_percent},
        {&Core::kcb_chs, &Core::kcb_pi, &Core::kcb_abs},
        {&Core::kcb_7, &Core::kcb_fix, &Core::kcb_deg},
        {&Core::kcb_8, &Core::kcb_sci, &Core::kcb_rad},
        {&Core::kcb_9, &Core::kcb_eng, &Core::kcb_grd},
        {&Core::kcb_div, &Core::kcb_x_mineq_y, &Core::kcb_x_min_0},
        {&Core::kcb_sst, &Core::kcb_lbl, &Core::kcb_bst},
        {&Core::kcb_gto, &Core::kcb_hyp, &Core::kcb_hyp_neg_1},
        {&Core::kcb_sin, &Core::kcb_x_xcng_i, &Core::kcb_sin_neg_1},
        {&Core::kcb_cos, &Core::kcb_i, &Core::kcb_cos_neg_1},
        {&Core::kcb_tan, &Core::kcb_I, &Core::kcb_tan_neg_1},
        {&Core::kcb_eex, &Core::kcb_to_r, &Core::kcb_to_p},
        {&Core::kcb_4, &Core::kcb_x_xcng_I, &Core::kcb_sf},
        {&Core::kcb_5, &Core::kcb_dse, &Core::kcb_cf},
        {&Core::kcb_6, &Core::kcb_isg, &Core::kcb_f_},
        {&Core::kcb_per, &Core::kcb_x_maj_y, &Core::kcb_x_maj_0},
        {&Core::kcb_r_s, &Core::kcb_pse, &Core::kcb_p_r},
        {&Core::kcb_gsb, &Core::kcb_sum, &Core::kcb_rtn},
        {&Core::kcb_r_dwn, &Core::kcb_prgm, &Core::kcb_r_up},
        {&Core::kcb_x_xcng_y, &Core::kcb_reg, &Core::kcb_rnd},
        {&Core::kcb_del, &Core::kcb_prefix, &Core::kcb_clx},
        {&Core::kcb_1, &Core::kcb_p_y_x, &Core::kcb_c_y_x},
        {&Core::kcb_2, &Core::kcb_to_hms, &Core::kcb_to_h},
        {&Core::kcb_3, &Core::kcb_to_rad, &Core::kcb_to_deg},
        {&Core::kcb_min, &Core::kcb_x_div_y, &Core::kcb_x_div_0},
        {&Core::kcb_off, &Core::kcb_off, &Core::kcb_off},
        {NULL, NULL, NULL},
        {NULL, NULL, NULL},
        {&Core::kcb_sto, &Core::kcb_frac, &Core::kcb_int},
        {&Core::kcb_rcl, &Core::kcb_user, &Core::kcb_mem},
        {&Core::kcb_0, &Core::kcb_x_, &Core::kcb_avg_x},
        {&Core::kcb_dot, &Core::kcb_y_r, &Core::kcb_s},
        {&Core::kcb_sum_plus, &Core::kcb_l_r, &Core::kcb_sum_minus},
        {&Core::kcb_plus, &Core::kcb_x_eq_y, &Core::kcb_x_eq_0},
        {&Core::kcb_enter, &Core::kcb_ran, &Core::kcb_lst_x},
    };
};

#endif // CORE_H
