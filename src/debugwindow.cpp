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

#include "debugwindow.h"

DebugWindow::DebugWindow(Signals *hpsignals_r)
: boxReg("Registers Dump"),
lab_reg("Register"),
lab_val("Value"),
lab_x("X"),
lab_y("Y"),
lab_z("Z"),
lab_t("T"),
lab_lst_x("LSTx"),
lab_x_val("0"),
lab_y_val("0"),
lab_z_val("0"),
lab_t_val("0"),
lab_lst_x_val("0"),
quitBtn("Chiudi") {
    hpsignals = hpsignals_r;

    try {
        /*
         * Sadly I can't use Gdk::Pixbuf::create_from_resource() because it's
         * available only in 3.12+ 
         */

        GError *error = NULL;

        icon = Gdk::Pixbuf::create_from_stream(Glib::wrap(g_resource_open_stream(resources_get_resource(), "/com/rapgenic/hp11em/images/icon.png", G_RESOURCE_LOOKUP_FLAGS_NONE, &error)));
    } catch (const Gdk::PixbufError& ex) {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }

    set_icon(icon);
    set_resizable(false);
    set_can_focus(true);
    grab_focus();

    hpsignals->signal_off().connect(sigc::mem_fun(*this, &DebugWindow::hide));
    hpsignals->signal_update_registers_table().connect(sigc::mem_fun(*this, &DebugWindow::update_table_registers));
    quitBtn.signal_clicked().connect(sigc::mem_fun(*this, &DebugWindow::hide));

    set_title("HP11C EDEBUG");
    set_border_width(3);

    add(windowGrid);

    windowGrid.add(boxReg);
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
    tableReg.attach_next_to(lab_lst_x, lab_x, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_t_val, lab_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_z_val, lab_t_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_y_val, lab_z_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_x_val, lab_y_val, Gtk::POS_BOTTOM, 1, 1);
    tableReg.attach_next_to(lab_lst_x_val, lab_x_val, Gtk::POS_BOTTOM, 1, 1);

    show_all_children();
}

DebugWindow::~DebugWindow() {
}

bool DebugWindow::update_table_registers(double x, double y, double z, double t, double lstx) {
    ostringstream tempstreamstring;

    tempstreamstring << scientific << setprecision(10) << x;
    lab_x_val.set_label(tempstreamstring.str());
    tempstreamstring.~ostringstream();
    new (&tempstreamstring) ostringstream();

    tempstreamstring << scientific << setprecision(10) << y;
    lab_y_val.set_label(tempstreamstring.str());
    tempstreamstring.~ostringstream();
    new (&tempstreamstring) ostringstream();

    tempstreamstring << scientific << setprecision(10) << z;
    lab_z_val.set_label(tempstreamstring.str());
    tempstreamstring.~ostringstream();
    new (&tempstreamstring) ostringstream();

    tempstreamstring << scientific << setprecision(10) << t;
    lab_t_val.set_label(tempstreamstring.str());
    tempstreamstring.~ostringstream();
    new (&tempstreamstring) ostringstream();

    tempstreamstring << scientific << setprecision(10) << lstx;
    lab_lst_x_val.set_label(tempstreamstring.str());

    return false;
}

#endif
