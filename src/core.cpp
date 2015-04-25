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

// <<TBD>> write the whole core

Core::Core(Signals *hpSignals_r) :
hpDisplay(hpSignals_r, &hpFlags) {
    // Initializing variables
    hpSignals = hpSignals_r;
    hpSignals->signal_key().connect(sigc::mem_fun(*this, &Core::keyPressEvent));

    // Initializing flags
    function_keys = F_NULL;
    hpTempDisp.cursor = 0;

    pending_data_count = 0;
}

Core::~Core() {
}

void Core::keyPressEvent(int key) {
    // Error state
    if (hpFlags.getState() == Flags::S_ERR) {
        hpFlags.setState(Flags::S_RUN);
        hpDisplay.printNumberDisplay(hpAMS.get_x());
        return;
    }

    // Reads the pressed key and decides what to do
    switch (key) {
        case Keys::K_SDF:
        case Keys::K_GDF:
            f_key_toggle(key);
            break;

        case -1:
            // Doesn't do anything, just called when pressing
            // something which isn't a button
            break;
        default:
            if (hpFlags.isPendingData()) {
                hpPendingData[pending_data_count].key = key;
                hpPendingData[pending_data_count].fg = function_keys;
                pending_data_count++;
                (this->*pending_data_function)();
            } else {
                (this->*keys_cb[key][function_keys])();
            }
            f_key_set(F_NULL);
#ifdef DEBUG
            hpSignals->sig_update_register_table_emit(double_approx(hpAMS.get_x()), double_approx(hpAMS.get_y()), double_approx(hpAMS.get_z()), double_approx(hpAMS.get_t()), double_approx(hpAMS.get_lst_x()));
            //            hpsignals->sig_update_decimal_emit(hpFlags.isDecimal(), hpFlags.getDecimalCount());
            cout << "Pressed Key Number: " << key << endl;
#endif
            break;
    }
}

int Core::f_key_set(unsigned char value) {
    if (value == F_NULL) {
        function_keys = F_NULL;
        hpSignals->sig_alarm_emit(A_GDF, false);
        hpSignals->sig_alarm_emit(A_SDF, false);
    } else if (value == F_FKEY) {
        function_keys = F_FKEY;
        hpSignals->sig_alarm_emit(A_GDF, false);
        hpSignals->sig_alarm_emit(A_SDF, true);
    } else if (value == F_GKEY) {
        function_keys = F_GKEY;
        hpSignals->sig_alarm_emit(A_GDF, true);
        hpSignals->sig_alarm_emit(A_SDF, false);
    }

    return 1;
}

int Core::f_key_toggle(int key) {
    if (key == Keys::K_SDF) {
        if (function_keys == F_FKEY)
            f_key_set(F_NULL);
        else if (function_keys == F_NULL || function_keys == F_GKEY)
            f_key_set(F_FKEY);
    } else if (key == Keys::K_GDF) {
        if (function_keys == F_GKEY)
            f_key_set(F_NULL);
        else if (function_keys == F_NULL || function_keys == F_FKEY)
            f_key_set(F_GKEY);
    }
    return 1;
}

/*
 bool Core::AMS_add_figure_to_x(char number)
 {
 if (x_temp.counter < 10) {
 x_temp.number = x_temp.number * 10 + number;
 x_temp.counter++;
 } else {
 return false;
 }

 return true;
 }

 bool Core::DISPLAY_format_converter(double number, char* display_text)
 {

 }

 bool Core::DISPLAY_print_number(double number)
 {
 char* text;

 DISPLAY_format_converter(number, text);
 hpsignals->sig_display_emit(text);

 return true;
 }

 bool Core::DISPLAY_reset()
 {
 char *display_text = "+0D N N N N N N N N N";

 hpsignals->sig_display_emit(display_text);

 return true;
 }*/
