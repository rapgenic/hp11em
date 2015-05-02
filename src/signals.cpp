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

#include <sigc++/sigc++.h>
#include <string>
using std::string;

#include <cln/cln.h>

#include "signals.h"

Signals::Signals() {
}

Signals::~Signals() {
}

Signals::signal_t Signals::signal_off() {
    return sig_off;
}

void Signals::sig_off_emit() {
    sig_off.emit();
}

Signals::signal_alarm_t Signals::signal_alarm() {
    return sig_alarm;
}

void Signals::sig_alarm_emit(char alarm, bool state) {
    sig_alarm.emit(alarm, state);
}

Signals::signal_display_t Signals::signal_display() {
    return sig_display;
}

void Signals::sig_display_emit(string disp) {
    sig_display.emit(disp);
}

Signals::signal_key_t Signals::signal_key() {
    return sig_key;
}

void Signals::sig_key_emit(int key) {
    sig_key.emit(key);
}

#ifdef DEBUG

Signals::d_signal_register_table_t Signals::signal_update_registers_table() {
    return sig_register_table;
}

void Signals::sig_update_register_table_emit(cl_R x, cl_R y, cl_R z, cl_R t, cl_R lstx) {
    sig_register_table.emit(x, y, z, t, lstx);
}

#endif

Signals::signal_t Signals::signal_menu() {
    return sig_menu;
}

void Signals::sig_menu_emit() {
    sig_menu.emit();
}

Signals::signal_window_move_t Signals::signal_window_move() {
    return sig_window_move;
}

void Signals::sig_window_move_emit(double x, double y) {
    sig_window_move.emit(x, y);
}