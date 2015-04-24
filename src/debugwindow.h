/*
 * debugwindow.h
 *
 *  Created on: 31/lug/2014
 *      Author: giulio
 */

#include "config.h"


#ifdef DEBUG

#ifndef DEBUGWINDOW_H_
#define DEBUGWINDOW_H_

#include "icon.xpm"

#include "signals.h"

#include <iostream>
#include <string>
using std::to_string;

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class DebugWindow : public Gtk::Window {
public:
    DebugWindow(Signals *hpsignals_r);
    virtual ~DebugWindow();

protected:
    Signals *hpsignals;

    Gtk::Grid windowGrid;
    Gtk::Frame boxReg/*, boxDec*/;
    Gtk::Grid tableReg, tableDec;
    Gtk::Label lab_reg, lab_val; //_lab_reg, _lab_val;
    Gtk::Label lab_x, lab_y, lab_z, lab_t;
    Gtk::Label lab_x_val, lab_y_val, lab_z_val, lab_t_val;
    //        Gtk::Label lab_isdec, lab_decount;
    //        Gtk::Label lab_isdec_val, lab_decount_val;
    Gtk::Button quitBtn;

    Glib::RefPtr<Gdk::Pixbuf> icon;

    bool update_table_registers(double x, double y, double z, double t);
    //        bool update_decimal(bool isdec, int deccount);
};

#endif /* DEBUGWINDOW_H_ */

#endif
