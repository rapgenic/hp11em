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
#ifdef DEBUG
    typedef sigc::signal<bool, double, double, double, double> d_signal_register_table_t;
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
    void sig_update_register_table_emit(double x, double y, double z, double t);

    //        d_signal_decimal_t signal_update_decimal();
    //        void sig_update_decimal_emit(bool isDecimal, int decimalCount);

#endif

    // GUI to core
    signal_key_t signal_key();
    void sig_key_emit(int key);

    // GUI to GUI
    signal_t signal_menu();
    void sig_menu_emit();

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
};

#endif // SIGNALS_H
