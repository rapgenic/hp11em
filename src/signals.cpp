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

#include "signals.h"

Signals::Signals() {}

Signals::~Signals() {}

Signals::signal_t Signals::signal_off() { return sig_off; }

void Signals::sig_off_emit() { sig_off.emit(); }

Signals::signal_alarm_t Signals::signal_alarm() { return sig_alarm; }

void Signals::sig_alarm_emit(char alarm, bool state) {
  sig_alarm.emit(alarm, state);
}

Signals::signal_display_t Signals::signal_display() { return sig_display; }

void Signals::sig_display_emit(std::string disp) { sig_display.emit(disp); }

Signals::signal_input_t Signals::signal_input() { return sig_key; }

void Signals::sig_input_emit(int key) { sig_key.emit(key); }

Signals::signal_t Signals::signal_gui_ready() { return sig_gui_ready; }

void Signals::sig_gui_ready_emit() { sig_gui_ready.emit(); }

Signals::signal_t Signals::signal_reset() { return sig_reset; }

void Signals::sig_reset_emit() { sig_reset.emit(); }

#ifdef DEBUG

Signals::d_signal_register_table_t Signals::signal_update_registers_table() {
  return sig_register_table;
}

void Signals::sig_update_register_table_emit(double x, double y, double z,
                                             double t, double lstx) {
  sig_register_table.emit(x, y, z, t, lstx);
}

#endif

Signals::signal_t Signals::signal_debug_window_toggle() {
  return sig_debug_window_toggle;
}

void Signals::sig_debug_window_toggle_emit() { sig_debug_window_toggle.emit(); }

Signals::signal_t Signals::signal_back_window_toggle() {
  return sig_back_window_toggle;
}

void Signals::sig_back_window_toggle_emit() { sig_back_window_toggle.emit(); }

Signals::signal_t Signals::signal_minimize() { return sig_minimize; }

void Signals::sig_minimize_emit() { sig_minimize.emit(); }

Signals::signal_window_move_t Signals::signal_window_move() {
  return sig_window_move;
}

void Signals::sig_window_move_emit(double x, double y) {
  sig_window_move.emit(x, y);
}
