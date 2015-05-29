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

#ifndef SIGNALS_H
#define SIGNALS_H

#include "config.h"

#include <sigc++/sigc++.h>
#include <string>
using std::string;

class Signals {
public:
    Signals();
    ~Signals();

    // Core to GUI
    typedef sigc::signal<void> signal_t;
    typedef sigc::signal<bool, char, bool> signal_alarm_t;
    typedef sigc::signal<bool, string> signal_display_t;
    typedef sigc::signal<bool, double, double> signal_window_move_t;
#ifdef DEBUG
    typedef sigc::signal<bool, double, double, double, double, double> d_signal_register_table_t;
    //        typedef sigc::signal<bool, bool, int> d_signal_decimal_t;
#endif

    // GUI to core
    typedef sigc::signal<void, int> signal_key_t;

    // Core to GUI
    signal_t signal_off();
    void sig_off_emit();

    signal_alarm_t signal_alarm();
    void sig_alarm_emit(char alarm, bool state);

    signal_display_t signal_display();
    void sig_display_emit(string disp);

#ifdef DEBUG

    d_signal_register_table_t signal_update_registers_table();
    void sig_update_register_table_emit(double x, double y, double z, double t, double lstx);

    //        d_signal_decimal_t signal_update_decimal();
    //        void sig_update_decimal_emit(bool isDecimal, int decimalCount);

#endif

    // GUI to core
    signal_key_t signal_key();
    void sig_key_emit(int key);

    // GUI to GUI
    signal_t signal_menu();
    void sig_menu_emit();

    signal_window_move_t signal_window_move();
    void sig_window_move_emit(double x, double y);

private:
    // Core to GUI
    signal_t sig_off;
    signal_alarm_t sig_alarm;
    signal_display_t sig_display;
#ifdef DEBUG
    d_signal_register_table_t sig_register_table;
    //        d_signal_decimal_t sig_decimal;
#endif

    // GUI to core
    signal_key_t sig_key;

    // GUI to GUI
    signal_t sig_menu;
    signal_window_move_t sig_window_move;
};

#endif // SIGNALS_H
