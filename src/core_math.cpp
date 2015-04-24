/*
 * core_math.cpp
 *
 *  Created on: 26/lug/2014
 *      Author: giulio
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
    hpDisplay.printNumberDisplay(hpAMS.get_x());
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

void Core::kcb_cl_x() {
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
}

void Core::kcb_frac() {
}

void Core::kcb_int() {
}

void Core::kcb_rcl() {
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
            hpAMS.set_x(hpAMS.get_y() / hpAMS.get_x());
            break;
    }

    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());

    hpDisplay.printNumberDisplay(hpAMS.get_x());

    reset_number();
    hpFlags.setStackDisabled(false);
}

void Core::reset_number() {
    //hpFlags.setpenEnter(true);
    //hpFlags.resDecimal();
    hpTempDisp.cursor = 0;
}