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

#include "core.h"

void Core::kcb_sqrt() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_alpha_a() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_x_2() {
    hpAMS.set_x(square(hpAMS.get_x()));

    hpDisplay.printNumberDisplay(hpAMS.get_x());
    reset_number();
}

void Core::kcb_e_x() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_alpha_b() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_ln() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_10_x() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_alpha_c() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_log() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_y_x() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_alpha_d() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_percent() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_1_x() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_alpha_e() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_d_percent() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_chs() {
    if (hpTempDisp.cursor == 0) {
        // if it is the result of an operation
        hpAMS.set_x(hpAMS.get_x() * -1, false);
        hpDisplay.printNumberDisplay(hpAMS.get_x());
        // Enable stack lift
        hpFlags.setStackDisabled(false);
    } else {
        // if you're writing
        if (hpTempDisp.str[0] == '-')
            hpTempDisp.str[0] = '+';
        else
            hpTempDisp.str[0] = '-';
        hpAMS.set_x(hpTempDisp.str, false);
        hpDisplay.printStringDisplay(hpTempDisp.str);
        // Don't change stack lift status: neutral function
    }
}

void Core::kcb_pi() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_abs() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_7() {
    kcb_c_number(7);
}

void Core::kcb_fix() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_deg() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_8() {
    kcb_c_number(8);
}

void Core::kcb_sci() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_rad() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_9() {
    kcb_c_number(9);
}

void Core::kcb_eng() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_grd() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_div() {
    kcb_c_stdopr(O_DIV);
}

void Core::kcb_x_mineq_y() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_x_min_0() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_sst() {
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_lbl() {
}

void Core::kcb_bst() {
}

void Core::kcb_gto() {
}

void Core::kcb_hyp() {
}

void Core::kcb_hyp_neg_1() {
}

void Core::kcb_sin() {
}

void Core::kcb_x_xcng_i() {
}

void Core::kcb_sin_neg_1() {
}

void Core::kcb_cos() {
}

void Core::kcb_i() {
}

void Core::kcb_cos_neg_1() {
}

void Core::kcb_tan() {
}

void Core::kcb_I() {
}

void Core::kcb_tan_neg_1() {
}

void Core::kcb_eex() {
}

void Core::kcb_to_r() {
}

void Core::kcb_to_p() {
}

void Core::kcb_4() {
    kcb_c_number(4);
}

void Core::kcb_x_xcng_I() {
}

void Core::kcb_sf() {
}

void Core::kcb_5() {
    kcb_c_number(5);
}

void Core::kcb_dse() {
}

void Core::kcb_cf() {
}

void Core::kcb_6() {
    kcb_c_number(6);
}

void Core::kcb_isg() {
}

void Core::kcb_f_() {
}

void Core::kcb_per() {
    kcb_c_stdopr(O_MLT);
}

void Core::kcb_x_maj_y() {
}

void Core::kcb_x_maj_0() {
}

void Core::kcb_r_s() {
}

void Core::kcb_pse() {
}

void Core::kcb_p_r() {
}

void Core::kcb_gsb() {
}

void Core::kcb_sum() {
}

void Core::kcb_rtn() {
}

void Core::kcb_r_dwn() {
    cl_R temp = hpAMS.get_x();
    hpAMS.set_x(hpAMS.get_y(), false);
    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());
    hpAMS.set_t(temp);
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_prgm() {
}

void Core::kcb_r_up() {
    cl_R temp = hpAMS.get_t();
    hpAMS.set_t(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_y());
    hpAMS.set_y(hpAMS.get_x());
    hpAMS.set_x(temp, false);
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_x_xcng_y() {
    cl_R temp = hpAMS.get_x();
    hpAMS.set_x(hpAMS.get_y());
    hpAMS.set_y(temp);
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

void Core::kcb_reg() {
}

void Core::kcb_rnd() {
}

void Core::kcb_del() {

}

void Core::kcb_prefix() {
}

void Core::kcb_clx() {
    hpAMS.set_x(static_cast<cl_R> (0), false);
    hpDisplay.printNumberDisplay(hpAMS.get_x());
    hpFlags.setStackDisabled(true);
}

void Core::kcb_1() {
    kcb_c_number(1);
}

void Core::kcb_p_y_x() {
}

void Core::kcb_c_y_x() {
}

void Core::kcb_2() {
    kcb_c_number(2);
}

void Core::kcb_to_hms() {
}

void Core::kcb_to_h() {
}

void Core::kcb_3() {
    kcb_c_number(3);
}

void Core::kcb_to_rad() {
}

void Core::kcb_to_deg() {
}

void Core::kcb_min() {
    kcb_c_stdopr(O_SUB);
}

void Core::kcb_x_div_y() {
}

void Core::kcb_x_div_0() {
}

void Core::kcb_off() {
    hpSignals->sig_off_emit();
}

void Core::kcb_sto() {
    kcb_c_sto_rcl(1);
}

void Core::kcb_frac() {
}

void Core::kcb_int() {
}

void Core::kcb_rcl() {
    kcb_c_sto_rcl(0);
}

void Core::kcb_user() {
}

void Core::kcb_mem() {
}

void Core::kcb_0() {
    kcb_c_number(0);
}

void Core::kcb_x_() {
}

void Core::kcb_avg_x() {
}

void Core::kcb_dot() {
    //    hpFlags.setDecimal(true);
    //    hpFlags.incDecimalCount();
    hpTempDisp.str[hpTempDisp.cursor] = '.';
    hpTempDisp.str[hpTempDisp.cursor + 1] = '\0';
    hpTempDisp.cursor++;

    hpDisplay.printStringDisplay(hpTempDisp.str);
}

void Core::kcb_y_r() {
}

void Core::kcb_s() {
}

void Core::kcb_sum_plus() {
    hpFlags.setStackDisabled(true);
}

void Core::kcb_l_r() {
}

void Core::kcb_sum_minus() {
    hpFlags.setStackDisabled(true);
}

void Core::kcb_plus() {
    kcb_c_stdopr(O_ADD);
}

void Core::kcb_x_eq_y() {
}

void Core::kcb_x_eq_0() {
}

void Core::kcb_enter() {
    hpAMS.stack_add(hpAMS.get_x());
    hpDisplay.printNumberDisplay(hpAMS.get_x());

    reset_number();
    hpFlags.setStackDisabled(true);
}

void Core::kcb_ran() {
}

void Core::kcb_lst_x() {
    hpAMS.stack_add(hpAMS.get_lst_x());
    hpDisplay.printNumberDisplay(hpAMS.get_x());
}

/* 
 * COMMON FUNCTIONS
 */

void Core::kcb_c_number(int n) {
    //if (hpFlags.penEnter())
    //    hpAMS.set_x("0");

    //    hpFlags.setDisplayWMode(Flags::M_DGT); /// ???????    
    if (hpTempDisp.cursor == 0) {
        hpTempDisp.str[0] = '+';
        hpTempDisp.cursor++;
    }

    /*if (hpTempDisp.cursor == 1 && hpFlags.isstackdisabled() == false) {
        hpAMS.stack_add("0");
    } 

    if (hpFlags.isstackdisabled() == true) {
        hpFlags.setstackdisabled(false);
    }*/

    hpTempDisp.str[hpTempDisp.cursor] = 48 + n; // Number 0 is ascii 48
    hpTempDisp.str[hpTempDisp.cursor + 1] = '\0';
    hpTempDisp.cursor++;

    // If it is the first digit
    if (hpTempDisp.cursor == 2) {
        if (hpFlags.isStackDisabled() == false) {
            hpAMS.stack_add(hpTempDisp.str);
        } else if (hpFlags.isStackDisabled() == true) {
            hpAMS.set_x(hpTempDisp.str, false);
            hpFlags.setStackDisabled(false);
        }
    } else {
        hpAMS.set_x(hpTempDisp.str, false);
    }

    /*
    
    if (hpFlags.isDecimal()) {
        hpAMS.set_x(hpAMS.get_x()+(static_cast<float> (n) / pow(10, hpFlags.getDecimalCount())));
        hpFlags.incDecimalCount();
    } else
        hpAMS.set_x(hpAMS.get_x()*10 + n);
     */

    hpDisplay.printStringDisplay(hpTempDisp.str);
}

void Core::kcb_c_stdopr(operators op) {
    switch (op) {
        case O_ADD:
            hpAMS.set_x(hpAMS.get_y() + hpAMS.get_x());
            break;
        case O_SUB:
            hpAMS.set_x(hpAMS.get_y() - hpAMS.get_x());
            break;
        case O_MLT:
            hpAMS.set_x(hpAMS.get_y() * hpAMS.get_x());
            break;
        case O_DIV:
            if (hpAMS.get_x() == 0) {
                hpFlags.setState(Flags::S_ERR);
                hpDisplay.printErrorDisplay(E_IMO);
                return;
            }
            hpAMS.set_x(hpAMS.get_y() / hpAMS.get_x());
            break;
    }

    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());

    hpDisplay.printNumberDisplay(hpAMS.get_x());

    reset_number();
    hpFlags.setStackDisabled(false);
}

void Core::kcb_c_sto_rcl(int storcl) {
    static int dot_pressed = 0;

    if (!hpFlags.isPendingData()) {
        hpFlags.setPendingData(true);

        if (storcl)
            pending_data_function = &Core::kcb_sto;
        else
            pending_data_function = &Core::kcb_rcl;

    } else {
        if (hpPendingData[pending_data_count - 1].fg == F_NULL && KEY_IS_NUMBER(hpPendingData[pending_data_count - 1].key)) {
            int loc = -1;
            switch (hpPendingData[pending_data_count - 1].key) {
                case Keys::K_NO0:
                    loc = 0;
                    break;
                case Keys::K_NO1:
                    loc = 1;
                    break;
                case Keys::K_NO2:
                    loc = 2;
                    break;
                case Keys::K_NO3:
                    loc = 3;
                    break;
                case Keys::K_NO4:
                    loc = 4;
                    break;
                case Keys::K_NO5:
                    loc = 5;
                    break;
                case Keys::K_NO6:
                    loc = 6;
                    break;
                case Keys::K_NO7:
                    loc = 7;
                    break;
                case Keys::K_NO8:
                    loc = 8;
                    break;
                case Keys::K_NO9:
                    loc = 9;
                    break;
            }
            if (dot_pressed) {
                loc += 10;
                dot_pressed = 0;
            }

            if (storcl)
                hpSR.sr_loc_set(0, hpAMS.get_x());
            else
                hpAMS.stack_add(hpSR.sr_loc_get(loc));

            hpDisplay.printNumberDisplay(hpAMS.get_x());
            reset_number();
            hpFlags.setStackDisabled(false);
            hpFlags.setPendingData(false);
            pending_data_count = 0;
        } else if (hpPendingData[0].fg == F_FKEY && hpPendingData[0].key == Keys::K_TAN) {
            if (storcl)
                hpSR.sr_loc_set(20, hpAMS.get_x());
            else
                hpAMS.stack_add(hpSR.sr_loc_get(20));
            
            hpDisplay.printNumberDisplay(hpAMS.get_x());
            reset_number();
            hpFlags.setStackDisabled(false);
            hpFlags.setPendingData(false);
            pending_data_count = 0;
        } else if (hpPendingData[pending_data_count - 1].fg == F_NULL && hpPendingData[pending_data_count - 1].key == Keys::K_DOT) {
            dot_pressed = 1;
            return;
        } else {
            pending_data_count = 0;
            dot_pressed = 0;
            hpFlags.setPendingData(false);
        }
    }
}

void Core::reset_number() {
    //hpFlags.setpenEnter(true);
    //hpFlags.resDecimal();
    hpTempDisp.cursor = 0;
}