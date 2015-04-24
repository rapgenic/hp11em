#include "signals.h"

#ifdef _LINUX__

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

void Signals::sig_update_register_table_emit(double x, double y, double z, double t) {
    sig_register_table.emit(x, y, z, t);
}

/*Signals::d_signal_decimal_t Signals::signal_update_decimal() {
    return sig_decimal;
}*/

/*void Signals::sig_update_decimal_emit(bool isDecimal, int decimalCount) {
    sig_decimal.emit(isDecimal, decimalCount);
}*/

#endif

Signals::signal_t Signals::signal_menu() {
    return sig_menu;
}

void Signals::sig_menu_emit() {
    sig_menu.emit();
}

#endif

#ifdef _ANDROID__
#endif

#ifdef _WINDOWS__
#endif
