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

#ifdef DEBUG

#ifndef DEBUGWINDOW_H_
#define DEBUGWINDOW_H_

#include <iostream>
#include <ostream>
using std::ostringstream;

#include <iomanip>
using std::setprecision;
using std::scientific;

#include <string>
#include <gtkmm.h>

#include "hpresources_external.h"
#include "signals.h"

class DebugWindow: public Gtk::Window {
public:
        DebugWindow(Signals *hpsignals_r);
        virtual ~DebugWindow();

protected:
        Signals *hpsignals;

        Gtk::Grid windowGrid;
        Gtk::Frame boxReg;
        Gtk::Grid tableReg;
        Gtk::Label lab_reg, lab_val;
        Gtk::Label lab_x, lab_y, lab_z, lab_t, lab_lst_x;
        Gtk::Label lab_x_val, lab_y_val, lab_z_val, lab_t_val, lab_lst_x_val;
        Gtk::Button quitBtn;

        Glib::RefPtr<Gdk::Pixbuf> icon;

        bool update_table_registers(double x, double y, double z, double t, double lstx);
};

#endif /* DEBUGWINDOW_H_ */

#endif
