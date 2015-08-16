/*
    Copyright (C) 2015 Giulio Girardi.

    This file is part of HP11em.

    HP11em is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HP11em is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HP11em.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "core.h"

void Core::kcb_sqrt() {
    hpAMS.set_x(sqrt(hpAMS.get_x()));
}

void Core::kcb_alpha_a() {
    return;
}

void Core::kcb_x_2() {
    hpAMS.set_x(pow(hpAMS.get_x(), 2));
}

void Core::kcb_e_x() {
    return;
}

void Core::kcb_alpha_b() {
    return;
}

void Core::kcb_ln() {
    hpAMS.set_x(log(hpAMS.get_x()));
}

void Core::kcb_10_x() {
    hpAMS.set_x(pow(10, hpAMS.get_x()));
}

void Core::kcb_alpha_c() {
    return;
}

void Core::kcb_log() {
    hpAMS.set_x(log10(hpAMS.get_x()));
}

void Core::kcb_y_x() {
    return;
}

void Core::kcb_alpha_d() {
    return;
}

void Core::kcb_percent() {
    return;
}

void Core::kcb_1_x() {
    return;
}

void Core::kcb_alpha_e() {
    return;
}

void Core::kcb_d_percent() {
    return;
}

void Core::kcb_chs() {
    switch (status) {
            /*
             * TODO: Check what is the real behaviour of CHS in IDLE state
             */
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(hpAMS.get_x()*-1, false);
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_pi() {
    if (stack_nolift_required) {
        hpAMS.set_x(C_PI);
        stack_nolift_required = false;
    } else {
        hpAMS.stack_add(C_PI);
    }
}

void Core::kcb_abs() {
    hpAMS.set_x(abs(hpAMS.get_x()));
}

void Core::kcb_7() {
    kcb_common_number(7);
    return;
}

void Core::kcb_fix() {
    if (status == S_WAITDATA) {
        if ((waiting_data[waiting_data_len - 1].fg == F_NONE && KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key))) {
            notation = N_FIX;
            precision = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
        }
        status = S_IDLE;
    }
}

void Core::kcb_deg() {
    return;
}

void Core::kcb_8() {
    kcb_common_number(8);
    return;
}

void Core::kcb_sci() {
    if (status == S_WAITDATA) {
        if ((waiting_data[waiting_data_len - 1].fg == F_NONE && KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key))) {
            notation = N_SCI;
            precision = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
        }
        status = S_IDLE;
    }
}

void Core::kcb_rad() {
    return;
}

void Core::kcb_9() {
    kcb_common_number(9);
    return;
}

void Core::kcb_eng() {
    if (status == S_WAITDATA) {
        if ((waiting_data[waiting_data_len - 1].fg == F_NONE && KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key))) {
            notation = N_ENG;
            precision = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
        }
        status = S_IDLE;
    }
}

void Core::kcb_grd() {
    return;
}

void Core::kcb_div() {
    if (hpAMS.get_x() == 0) {
        status = S_ERR;
        error = E_IMO;
        return;
    }
    hpAMS.set_x(hpAMS.get_y() / hpAMS.get_x());
    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());
    return;
}

void Core::kcb_x_mineq_y() {
    return;
}

void Core::kcb_x_min_0() {
    return;
}

void Core::kcb_sst() {
    return;
}

void Core::kcb_lbl() {
    return;
}

void Core::kcb_bst() {
    return;
}

void Core::kcb_gto() {
    return;
}

void Core::kcb_hyp() {
    return;
}

void Core::kcb_hyp_neg_1() {
    return;
}

void Core::kcb_sin() {
    return;
}

void Core::kcb_x_xcng_i() {
    return;
}

void Core::kcb_sin_neg_1() {
    return;
}

void Core::kcb_cos() {
    return;
}

void Core::kcb_i() {
    return;
}

void Core::kcb_cos_neg_1() {
    return;
}

void Core::kcb_tan() {
    return;
}

void Core::kcb_I() {
    return;
}

void Core::kcb_tan_neg_1() {
    return;
}

void Core::kcb_eex() {
    return;
}

void Core::kcb_to_r() {
    return;
}

void Core::kcb_to_p() {
    return;
}

void Core::kcb_4() {
    kcb_common_number(4);
    return;
}

void Core::kcb_x_xcng_I() {
    return;
}

void Core::kcb_sf() {
    return;
}

void Core::kcb_5() {
    kcb_common_number(5);
    return;
}

void Core::kcb_dse() {
    return;
}

void Core::kcb_cf() {
    return;
}

void Core::kcb_6() {
    kcb_common_number(6);
    return;
}

void Core::kcb_isg() {
    return;
}

void Core::kcb_f_() {
    return;
}

void Core::kcb_per() {
    hpAMS.set_x(hpAMS.get_y() * hpAMS.get_x());
    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());
    return;
}

void Core::kcb_x_maj_y() {
    return;
}

void Core::kcb_x_maj_0() {
    return;
}

void Core::kcb_r_s() {
    return;
}

void Core::kcb_pse() {
    return;
}

void Core::kcb_p_r() {
    return;
}

void Core::kcb_gsb() {
    return;
}

void Core::kcb_sum() {
    return;
}

void Core::kcb_rtn() {
    return;
}

void Core::kcb_r_dwn() {
    double temp = hpAMS.get_x();
    hpAMS.set_x(hpAMS.get_y(), false);
    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());
    hpAMS.set_t(temp);
}

void Core::kcb_prgm() {
    return;
}

void Core::kcb_r_up() {
    double temp = hpAMS.get_t();
    hpAMS.set_t(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_y());
    hpAMS.set_y(hpAMS.get_x());
    hpAMS.set_x(temp, false);
}

void Core::kcb_x_xcng_y() {
    double temp = hpAMS.get_x();
    hpAMS.set_x(hpAMS.get_y());
    hpAMS.set_y(temp);
}

void Core::kcb_reg() {
    return;
}

void Core::kcb_rnd() {
    return;
}

void Core::kcb_del() {
    return;
}

void Core::kcb_prefix() {
    return;
}

void Core::kcb_clx() {
    hpAMS.set_x(0.0, false);
}

void Core::kcb_1() {
    kcb_common_number(1);
    return;
}

void Core::kcb_p_y_x() {
    return;
}

void Core::kcb_c_y_x() {
    return;
}

void Core::kcb_2() {
    kcb_common_number(2);
    return;
}

void Core::kcb_to_hms() {
    return;
}

void Core::kcb_to_h() {
    return;
}

void Core::kcb_3() {
    kcb_common_number(3);
    return;
}

void Core::kcb_to_rad() {
    return;
}

void Core::kcb_to_deg() {
    return;
}

void Core::kcb_min() {
    hpAMS.set_x(hpAMS.get_y() - hpAMS.get_x());
    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());
    return;
}

void Core::kcb_x_div_y() {
    return;
}

void Core::kcb_x_div_0() {
    return;
}

void Core::kcb_sto() {
    return;
}

void Core::kcb_frac() {
    hpAMS.set_x(modf(hpAMS.get_x(), new double));
}

void Core::kcb_int() {
    double i;
    modf(hpAMS.get_x(), &i);
    hpAMS.set_x(i);
}

void Core::kcb_rcl() {
    return;
}

void Core::kcb_user() {
    return;
}

void Core::kcb_mem() {
    return;
}

void Core::kcb_0() {
    kcb_common_number(0);
    return;
}

void Core::kcb_x_() {
    return;
}

void Core::kcb_avg_x() {
    return;
}

void Core::kcb_dot() {
    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            decimal = true;
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_y_r() {
    return;
}

void Core::kcb_s() {
    return;
}

void Core::kcb_sum_plus() {
    return;
}

void Core::kcb_l_r() {
    return;
}

void Core::kcb_sum_minus() {
    return;
}

void Core::kcb_plus() {
    hpAMS.set_x(hpAMS.get_y() + hpAMS.get_x());
    hpAMS.set_y(hpAMS.get_z());
    hpAMS.set_z(hpAMS.get_t());
}

void Core::kcb_x_eq_y() {
    return;
}

void Core::kcb_x_eq_0() {
    return;
}

void Core::kcb_enter() {
    hpAMS.stack_add(hpAMS.get_x());
    stack_nolift_required = true;
}

void Core::kcb_ran() {
    return;
}

void Core::kcb_lst_x() {
    hpAMS.stack_add(hpAMS.get_lst_x());
}

void Core::kcb_common_number(int x) {
    if (x > 9) {
        return;
    }

    switch (status) {
        case S_IDLE:
            if (stack_nolift_required) {
                stack_nolift_required = false;
                hpAMS.set_x(x, false);
            } else {
                hpAMS.stack_add(x);
            }
            break;
        case S_INPUT:
            if (figures_number < 10) {
                if (!decimal) {
                    hpAMS.set_x(hpAMS.get_x()*10 + x, false);
                } else {
                    hpAMS.set_x(hpAMS.get_x()+(x / pow10(decimal_figures_number++)));
                }
            }
            break;
        case S_ERR:
            break;
        default:
            break;
    }

    if (!decimal) {
        if (hpAMS.get_x() != 0) {
            figures_number++;
        }
    } else {
        figures_number++;
    }
}

/*
 * FUNCTION TEMPLATE
 *
 *
void Core::function_template(int x) {
    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}
 */

int Core::c_get_val_from_key(int key) {
    switch (key) {
        case Keys::K_NO0:
            return 0;
            break;
        case Keys::K_NO1:
            return 1;
            break;
        case Keys::K_NO2:
            return 2;
            break;
        case Keys::K_NO3:
            return 3;
            break;
        case Keys::K_NO4:
            return 4;
            break;
        case Keys::K_NO5:
            return 5;
            break;
        case Keys::K_NO6:
            return 6;
            break;
        case Keys::K_NO7:
            return 7;
            break;
        case Keys::K_NO8:
            return 8;
            break;
        case Keys::K_NO9:
            return 9;
            break;
    }
}