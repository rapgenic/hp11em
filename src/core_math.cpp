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
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(sqrt(hpAMS.get_x()));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_alpha_a() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_x_2() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(pow(hpAMS.get_x(), 2));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_e_x() {
    switch (status) {
        case S_IDLE: 
        case S_INPUT:
            hpAMS.set_x(pow(C_E, hpAMS.get_x()));
            break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_alpha_b() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_ln() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(log(hpAMS.get_x()));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_10_x() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(pow(10, hpAMS.get_x()));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_alpha_c() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_log() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(log10(hpAMS.get_x()));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_y_x() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(pow(hpAMS.get_y(), hpAMS.get_x()));
            hpAMS.set_y(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_t());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_alpha_d() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_percent() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_1_x() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            if (hpAMS.get_x() == 0) {
                status = S_ERR;
                error = E_IMO;
                return;
            }
            hpAMS.set_x(1.0 / hpAMS.get_x());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_alpha_e() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_d_percent() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_chs() {
    switch (status) {
            /*
             * TODO: Check what is the real behaviour of CHS in IDLE state
             */
        case S_IDLE:
        case S_INPUT:
            if (exp) {
                int old_exp_val = exp_val;
                exp_val *= -1;
                hpAMS.set_x(hpAMS.get_x() / pow10(old_exp_val) * pow10(exp_val));
            } else
                hpAMS.set_x(hpAMS.get_x()*-1, false);
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_pi() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            if (stack_nolift_required) {
                hpAMS.set_x(C_PI);
                stack_nolift_required = false;
            } else {
                hpAMS.stack_add(C_PI);
            }
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_abs() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(abs(hpAMS.get_x()));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_7() {
    kcb_common_number(7);
}

void Core::kcb_fix() {
    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            break;
        case S_WAITDATA:
            if ((waiting_data[waiting_data_len - 1].fg == F_NONE && KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key))) {
                notation = N_FIX;
                precision = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
                status = S_IDLE;
            } else {
                ignore_waitdata();
            }
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_deg() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_8() {
    kcb_common_number(8);
}

void Core::kcb_sci() {
    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            break;
        case S_WAITDATA:
            if ((waiting_data[waiting_data_len - 1].fg == F_NONE && KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key))) {
                notation = N_SCI;
                precision = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
                status = S_IDLE;
            } else {
                ignore_waitdata();
            }
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_rad() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_9() {
    kcb_common_number(9);
}

void Core::kcb_eng() {
    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            break;
        case S_WAITDATA:
            if ((waiting_data[waiting_data_len - 1].fg == F_NONE && KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key))) {
                notation = N_ENG;
                precision = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
                status = S_IDLE;
            } else {
                ignore_waitdata();
            };
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_grd() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_div() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            if (hpAMS.get_x() == 0) {
                status = S_ERR;
                error = E_IMO;
                return;
            }
            hpAMS.set_x(hpAMS.get_y() / hpAMS.get_x());
            hpAMS.set_y(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_t());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_x_mineq_y() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_x_min_0() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sst() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_lbl() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_bst() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_gto() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_hyp() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_hyp_neg_1() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sin() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(sin(hpAMS.get_x()));
            break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_x_xcng_i() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sin_neg_1() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_cos() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(cos(hpAMS.get_x()));
            break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_i() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_cos_neg_1() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_tan() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(tan(hpAMS.get_x()));
            break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_I() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_tan_neg_1() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_eex() {
    switch (status) {
        case S_IDLE:
            hpAMS.set_x(1);
            figures_number++;
            exp = true;
            break;
        case S_INPUT:
            exp = true;
            break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_to_r() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_to_p() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_4() {
    kcb_common_number(4);
}

void Core::kcb_x_xcng_I() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sf() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_5() {
    kcb_common_number(5);
}

void Core::kcb_dse() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_cf() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_6() {
    kcb_common_number(6);
}

void Core::kcb_isg() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_f_() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_per() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(hpAMS.get_y() * hpAMS.get_x());
            hpAMS.set_y(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_t());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_x_maj_y() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_x_maj_0() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_r_s() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_pse() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_p_r() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_gsb() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sum() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_rtn() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_r_dwn() {
    double temp = hpAMS.get_x();
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(hpAMS.get_y(), false);
            hpAMS.set_y(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_t());
            hpAMS.set_t(temp);
            break;
        case S_ERR:
            break;
        default:
            break;
    }

}

void Core::kcb_prgm() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_r_up() {
    double temp = hpAMS.get_t();
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_t(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_y());
            hpAMS.set_y(hpAMS.get_x());
            hpAMS.set_x(temp, false);
            break;
        case S_ERR:
            break;
        default:
            break;
    }

}

void Core::kcb_x_xcng_y() {
    double temp = hpAMS.get_x();
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(hpAMS.get_y());
            hpAMS.set_y(temp);
            break;
        case S_ERR:
            break;
        default:
            break;
    }

}

void Core::kcb_reg() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpSR.sr_clear();
            break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_rnd() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_del() {
    switch (status) {
        case S_IDLE:
            hpAMS.set_x(0.0, false);
            stack_nolift_required = true;
            break;
        case S_INPUT:
            if (exp) {
                if (exp_val == 0) {
                    exp = 0;
                } else {
                    exp_val = exp_val / 10;
                }
            } else if (!decimal) {
                if (figures_number == 1) {
                    hpAMS.set_x(0.0, false);
                    stack_nolift_required = true;
                    /*
                     * Passing to IDLE state
                     */
                    reset_input_mode();
                    status = S_IDLE;
                } else {
                    hpAMS.set_x((long) (hpAMS.get_x() / 10), false);
                    figures_number--;
                }
            } else {
                if (decimal_figures_number == 2) {
                    decimal = false;
                }

                hpAMS.set_x(((double) ((long) (hpAMS.get_x() * pow10(decimal_figures_number - 1)))) / pow10(decimal_figures_number - 1));
                decimal_figures_number--;
                figures_number--;
            }
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_prefix() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_clx() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(0.0, false);
            stack_nolift_required = true;
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_1() {
    kcb_common_number(1);
}

void Core::kcb_p_y_x() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_c_y_x() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_2() {
    kcb_common_number(2);
}

void Core::kcb_to_hms() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_to_h() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_3() {
    kcb_common_number(3);
}

void Core::kcb_to_rad() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_to_deg() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_min() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(hpAMS.get_y() - hpAMS.get_x());
            hpAMS.set_y(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_t());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_x_div_y() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_x_div_0() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sto() {
    static int dot_pressed = 0;
    static int operation = -1;

    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            break;
        case S_WAITDATA:
            if ((waiting_data[waiting_data_len - 1].fg == F_NONE &&
                    KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key)) ||
                    (waiting_data[0].fg == F_FKEY &&
                    waiting_data[0].key == Keys::K_TAN)) {
                int loc = -1;
                if (waiting_data[waiting_data_len - 1].fg == F_NONE) {
                    loc = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
                    if (dot_pressed) {
                        loc += 10;
                        dot_pressed = 0;
                    }
                } else if (waiting_data[0].fg == F_FKEY &&
                        waiting_data[0].key == Keys::K_TAN)
                    loc = 20;

                if (operation == -1)
                    hpSR.sr_loc_set(loc, hpAMS.get_x());
                else if (operation == 0)
                    hpSR.sr_loc_set(loc, hpSR.sr_loc_get(loc) + hpAMS.get_x());
                else if (operation == 1)
                    hpSR.sr_loc_set(loc, hpSR.sr_loc_get(loc) - hpAMS.get_x());
                else if (operation == 2)
                    hpSR.sr_loc_set(loc, hpSR.sr_loc_get(loc) * hpAMS.get_x());
                else if (operation == 3)
                    hpSR.sr_loc_set(loc, hpSR.sr_loc_get(loc) / hpAMS.get_x());

                status = S_IDLE;
                dot_pressed = 0;
                operation = -1;
            } else if (waiting_data[waiting_data_len - 1].fg == F_NONE && waiting_data[waiting_data_len - 1].key == Keys::K_DOT) {
                dot_pressed = 1;
            } else if (waiting_data[0].fg == F_NONE && waiting_data[0].key == Keys::K_PIU) {
                operation = 0;
            } else if (waiting_data[0].fg == F_NONE && waiting_data[0].key == Keys::K_MEN) {
                operation = 1;
            } else if (waiting_data[0].fg == F_NONE && waiting_data[0].key == Keys::K_PER) {
                operation = 2;
            } else if (waiting_data[0].fg == F_NONE && waiting_data[0].key == Keys::K_DIV) {
                operation = 3;
            } else {
                //status = S_IDLE;
                ignore_waitdata();
                dot_pressed = 0;
                operation = -1;
            }
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_frac() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(modf(hpAMS.get_x(), new double));
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_int() {
    double i;
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            modf(hpAMS.get_x(), &i);
            hpAMS.set_x(i);
            break;
        case S_ERR:
            break;
        default:
            break;
    }

}

void Core::kcb_rcl() {
    static int dot_pressed = 0;

    switch (status) {
        case S_IDLE:
            break;
        case S_INPUT:
            break;
        case S_WAITDATA:
            if ((waiting_data[waiting_data_len - 1].fg == F_NONE &&
                    KEY_IS_NUMBER(waiting_data[waiting_data_len - 1].key)) ||
                    (waiting_data[0].fg == F_FKEY &&
                    waiting_data[0].key == Keys::K_TAN)) {
                int loc = -1;
                if (waiting_data[waiting_data_len - 1].fg == F_NONE) {
                    loc = c_get_val_from_key(waiting_data[waiting_data_len - 1].key);
                    if (dot_pressed) {
                        loc += 10;
                        dot_pressed = 0;
                    }
                } else if (waiting_data[0].fg == F_FKEY &&
                        waiting_data[0].key == Keys::K_TAN) {
                    loc = 20;
                }

                hpAMS.stack_add(hpSR.sr_loc_get(loc));

                status = S_IDLE;
                dot_pressed = 0;
            } else if (waiting_data[waiting_data_len - 1].fg == F_NONE && waiting_data[waiting_data_len - 1].key == Keys::K_DOT) {
                dot_pressed = 1;
            } else {
                //status = S_IDLE;
                ignore_waitdata();
                dot_pressed = 0;
            }
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_user() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_mem() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_0() {
    kcb_common_number(0);
}

void Core::kcb_x_() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_avg_x() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
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
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_s() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sum_plus() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_l_r() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_sum_minus() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_plus() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.set_x(hpAMS.get_y() + hpAMS.get_x());
            hpAMS.set_y(hpAMS.get_z());
            hpAMS.set_z(hpAMS.get_t());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_x_eq_y() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_x_eq_0() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_enter() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.stack_add(hpAMS.get_x());
            stack_nolift_required = true;
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::kcb_ran() {
    switch (status) {
        case S_IDLE: break;
        case S_INPUT: break;
        case S_ERR: break;
        default: break;
    }
}

void Core::kcb_lst_x() {
    switch (status) {
        case S_IDLE:
        case S_INPUT:
            hpAMS.stack_add(hpAMS.get_lst_x());
            break;
        case S_ERR:
            break;
        default:
            break;
    }
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
            if (exp) {
                int old_exp_val = exp_val;
                exp_val %= 10;
                exp_val *= 10;
                exp_val += x;
                hpAMS.set_x(hpAMS.get_x() / pow10(old_exp_val) * pow10(exp_val));
            } else if (figures_number < 10) {
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

    if (!exp) {
        if (!decimal) {
            figures_number++;
            if (hpAMS.get_x() == 0)
                start_zero_figures_number++;

        } else {
            figures_number++;
        }
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