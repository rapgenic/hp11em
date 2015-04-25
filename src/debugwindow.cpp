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

#include "debugwindow.h"

#ifdef DEBUG

DebugWindow::DebugWindow(Signals *hpsignals_r)
: boxReg("Registers Dump"),
//boxDec("Decimal flags"),
lab_reg("Register"),
lab_val("Value"),
//_lab_reg("Register"),
//_lab_val("Value"),
lab_x("X"),
lab_y("Y"),
lab_z("Z"),
lab_t("T"),
lab_x_val("0"),
lab_y_val("0"),
lab_z_val("0"),
lab_t_val("0"),
//lab_isdec("isDecimal"),
//lab_decount("DecCount"),
//lab_isdec_val("false"),
//lab_decount_val("0"),
quitBtn("Chiudi") {
    hpsignals = hpsignals_r;

    try {
        icon = Gdk::Pixbuf::create_from_xpm_data(icon_xpm);
    } catch (const Gdk::PixbufError& ex) {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }

    set_icon(icon);
    set_resizable(false);
    set_can_focus(true);
    grab_focus();

    hpsignals->signal_off().connect(sigc::mem_fun(*this, &DebugWindow::hide));
    hpsignals->signal_update_registers_table().connect(sigc::mem_fun(*this, &DebugWindow::update_table_registers));
    //    hpsignals->signal_update_decimal().connect(sigc::mem_fun(*this, &DebugWindow::update_decimal));
    quitBtn.signal_clicked().connect(sigc::mem_fun(*this, &DebugWindow::hide));

    set_title("HP11C EDEBUG");
    set_border_width(3);

    add(windowGrid);

    windowGrid.add(boxReg);
    //    windowGrid.attach_next_to(boxDec, boxReg, Gtk::POS_BOTTOM, 1, 1);
    windowGrid.attach_next_to(quitBtn, boxReg, Gtk::POS_BOTTOM, 1, 1);

    boxReg.add(tableReg);

    tableReg.set_column_spacing(10);
    tableReg.set_border_width(3);
    tableReg.add(lab_reg);
    tableReg.add(lab_val);
    tableReg.attach_next_to(lab_t, lab_reg, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_z, lab_t, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_y, lab_z, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_x, lab_y, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_t_val, lab_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_z_val, lab_t_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_y_val, lab_z_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_x_val, lab_y_val, Gtk::POS_BOTTOM, 1, 1);

    /*    boxDec.add(tableDec);

        tableDec.set_column_spacing(10);
        tableDec.set_border_width(3);
        tableDec.add(_lab_reg);
        tableDec.add(_lab_val);
        tableDec.attach_next_to(lab_isdec, _lab_reg, Gtk::POS_BOTTOM, 1, 1);
        tableDec.attach_next_to(lab_decount, lab_isdec, Gtk::POS_BOTTOM, 1, 1);
        tableDec.attach_next_to(lab_isdec_val, _lab_val, Gtk::POS_BOTTOM, 1, 1);
        tableDec.attach_next_to(lab_decount_val, lab_isdec_val, Gtk::POS_BOTTOM, 1, 1);*/

    show_all_children();
}

DebugWindow::~DebugWindow() {
}

bool DebugWindow::update_table_registers(double x, double y, double z, double t) {
    lab_x_val.set_label(to_string(x));
    lab_y_val.set_label(to_string(y));
    lab_z_val.set_label(to_string(z));
    lab_t_val.set_label(to_string(t));

    return false;
}

/*bool DebugWindow::update_decimal(bool isdec, int deccount) {
    lab_isdec_val.set_label((isdec == true ? "True" : "False"));
    lab_decount_val.set_label(to_string(deccount));
}*/

#endif
