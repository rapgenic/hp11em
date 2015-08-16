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

Core::Core(Signals *hpSignals_r) {
    // Initializing variables
    hpSignals = hpSignals_r;
    hpSignals->signal_key().connect(sigc::mem_fun(*this, &Core::input));

    status = S_IDLE;
    error = E_NONE;
    fkeys = F_NONE;

    stack_nolift_required = false;

    decimal = false;
    exp = false;
    decimal_figures_number = 1;
    figures_number = 0;
    exp_val = 0;

    notation = N_FIX;
    precision = 4;

    waiting_data_len = 0;
}

Core::~Core() {
}

void Core::input(int key) {
    switch (key) {
        case Keys::K_SDF:
        case Keys::K_GDF:
            f_key_toggle(key);
            break;
        case Keys::K_ONF:
            hpSignals->sig_off_emit();
            break;
        default:
            switch (status) {
                case S_IDLE:
                    (this->*keys_cb[key][fkeys])();

                    switch (key_status[key][fkeys]) {
                        case S_INPUT:
                            status = S_INPUT;
                            break;
                        case S_WAITDATA:
                            waitdata_cb = keys_cb[key][fkeys];
                            waiting_data_len = 0;
                            status = S_WAITDATA;
                            break;
                    }

                    f_key_set(F_NONE);

                    display();

                    break;
                case S_INPUT:
                    (this->*keys_cb[key][fkeys])();

                    switch (key_status[key][fkeys]) {
                        case S_IDLE:
                            /*
                             * Resetting INPUT variables
                             */
                            decimal = false;
                            exp = false;
                            decimal_figures_number = 1;
                            figures_number = 0;
                            exp_val = 0;
                            status = S_IDLE;
                            break;
                        case S_WAITDATA:
                            waitdata_cb = keys_cb[key][fkeys];
                            waiting_data_len = 0;
                            status = S_WAITDATA;
                            break;
                    }

                    f_key_set(F_NONE);

                    display();

                    break;
                case S_WAITDATA:
                    waiting_data[waiting_data_len].key = key;
                    waiting_data[waiting_data_len].fg = fkeys;
                    waiting_data_len++;

                    (this->*waitdata_cb)();

                    display();

                    break;
                case S_ERR:
                    error = E_NONE;
                    status = S_IDLE;

                    display();

                    break;
                default:
                    break;
            }
#ifdef DEBUG
            hpSignals->sig_update_register_table_emit(hpAMS.get_x(), hpAMS.get_y(), hpAMS.get_z(), hpAMS.get_t(), hpAMS.get_lst_x());
            cerr << KBLU << "Pressed Key Number: " << key << KRST << endl;
#endif
            break;
    }
}

void Core::f_key_set(unsigned char value) {
    if (value == F_NONE) {
        fkeys = F_NONE;
        hpSignals->sig_alarm_emit(A_GDF, false);
        hpSignals->sig_alarm_emit(A_SDF, false);
    } else if (value == F_FKEY) {
        fkeys = F_FKEY;
        hpSignals->sig_alarm_emit(A_GDF, false);
        hpSignals->sig_alarm_emit(A_SDF, true);
    } else if (value == F_GKEY) {
        fkeys = F_GKEY;
        hpSignals->sig_alarm_emit(A_GDF, true);
        hpSignals->sig_alarm_emit(A_SDF, false);
    }
}

void Core::f_key_toggle(int key) {
    if (key == Keys::K_SDF) {
        if (fkeys == F_FKEY)
            f_key_set(F_NONE);
        else if (fkeys == F_NONE || fkeys == F_GKEY)
            f_key_set(F_FKEY);
    } else if (key == Keys::K_GDF) {
        if (fkeys == F_GKEY)
            f_key_set(F_NONE);
        else if (fkeys == F_NONE || fkeys == F_FKEY)
            f_key_set(F_GKEY);
    }
}

void Core::display() {
    double numb = hpAMS.get_x();
    // Assuring that numb doesn't get truncated
    if (numb > 0) {
        numb += 5.0 * pow10(-10.0);
    } else if (numb < 0) {
        numb -= 5.0 * pow10(-10.0);
    }
    // Working with positive numbers only
    double pnumb = fabs(numb);

    int expv = 0;
    int exppos = 0;
    long pnumbi = 0;
    double pnumbd = 0;
    char spnumbi[22] = "";
    char spnumbd[22] = "";
    char sexp[3] = "";

    char display_text[22] = "";

    switch (status) {
        case S_IDLE:
            if (notation == N_FIX && numb < pow10(10)) {
                pnumbi = (long) pnumb;
                pnumbd = pnumb - (double) pnumbi;

                longToString(pnumbi, spnumbi, 1);
                longToString((long) (pnumbd * pow(10, precision)), spnumbd, precision);

                sprintf(display_text, "%c%s,%s", numb >= 0 ? '+' : '-', spnumbi, spnumbd);
            } else if (notation == N_SCI || (notation == N_FIX && numb > pow10(10))) {
                //double tpnumb = pnumb;

                // calculates the exponent
                if (pnumb >= 10.0) {
                    while (pnumb >= 10.0) {
                        pnumb /= 10.0;
                        expv++;
                    }
                } else if (pnumb == 0) {
                    expv = 0;
                } else if (pnumb < 1.0) {
                    while (pnumb < 1.0) {
                        pnumb *= 10.0;
                        expv--;
                    }
                }

                pnumbi = (long) pnumb;
                pnumbd = pnumb - (double) pnumbi;

                longToString(pnumbi, spnumbi, 1);
                longToString((long) (pnumbd * pow10(precision)), spnumbd, precision);

                sprintf(display_text, "%c%s,%s", numb >= 0 ? '+' : '-', spnumbi, spnumbd);

                // Adding exponent to string
                longToString(abs(expv), sexp, 2);

                // calculate the position of the exponent in the display:
                // we need to do all these strange calculations because only
                // figures are considered while converting the string to 
                // display lines so for example a string like this
                //    "+1.1111"
                // is a 7 char string, but when printing to the display
                // only
                //    "11111"
                // are considered.
                // in conclusion '+' '-' '.' ',' aren't considered as a character

                exppos = strlen(display_text)+(10 - (strlen(spnumbi) + strlen(spnumbd)));

                for (int h = strlen(display_text); h < 22; h++)
                    display_text[h] = ' ';

                // insert a space or a minus before the exponent to distinguish it from the rest of
                // the number
                display_text[exppos - 3] = expv >= 0 ? ' ' : '-';
                display_text[exppos - 2] = sexp[0];
                display_text[exppos - 1] = sexp[1];
                display_text[exppos] = '\0';
            }

            hpSignals->sig_display_emit(display_text);
            break;
        case S_INPUT:
            if (exp) {
                pnumb /= pow10(exp_val);
            }

            pnumbi = (long) pnumb;
            pnumbd = pnumb - (double) pnumbi;

            longToString(pnumbi, spnumbi, 1);
            longToString((long) (pnumbd * pow(10, decimal_figures_number - 1)), spnumbd, decimal_figures_number - 1);

            sprintf(display_text, "%c", numb >= 0 ? '+' : '-');
            strcat(display_text, spnumbi);
            if (decimal) {
                strcat(display_text, ",");
                strcat(display_text, spnumbd);
            }

            if (exp) {
                // Adding exponent to string
                longToString(abs(exp_val), sexp, 2);

                // calculate the position of the exponent in the display:
                // we need to do all these strange calculations because only
                // figures are considered while converting the string to 
                // display lines so for example a string like this
                //    "+1.1111"
                // is a 7 char string, but when printing to the display
                // only
                //    "11111"
                // are considered.
                // in conclusion '+' '-' '.' ',' aren't considered as a character

                exppos = strlen(display_text)+(10 - (strlen(spnumbi) + strlen(spnumbd)));

                for (int h = strlen(display_text); h < 22; h++)
                    display_text[h] = ' ';

                // insert a space or a minus before the exponent to distinguish it from the rest of
                // the number
                display_text[exppos - 3] = expv >= 0 ? ' ' : '-';
                display_text[exppos - 2] = sexp[0];
                display_text[exppos - 1] = sexp[1];
                display_text[exppos] = '\0';
            }

            hpSignals->sig_display_emit(display_text);
            break;
        case S_ERR:
            break;
        default:
            break;
    }
}

void Core::longToString(long x, char str[], int d) {
    int i = 0;
    int z = 0;
    int j;
    int temp;

    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    // reversing string
    j = i - 1;

    while (z < j) {
        temp = str[z];
        str[z] = str[j];
        str[j] = temp;
        z++;
        j--;
    }

    str[i] = '\0';
}