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

#include "mainwindow.h"

#include "colors.h"

MainWindow::MainWindow(Signals *hpsignals_r)
: calc(hpsignals_r)
#ifdef DEBUG
,hpDebug(hpsignals_r)
#endif
{
    // creates the user interface
    hpsignals = hpsignals_r;

    try {
        icon = Gdk::Pixbuf::create_from_xpm_data(icon_xpm);
    } catch (const Gdk::PixbufError& ex) {
        std::cerr << KRED << "PixbufError: " << ex.what() << KRST << std::endl;
    }

    set_icon(icon);
    set_resizable(false);
    set_decorated(false);

    hpsignals->signal_off().connect(sigc::mem_fun(*this, &MainWindow::hide));
    hpsignals->signal_menu().connect(sigc::mem_fun(*this, &MainWindow::menu_show));
    hpsignals->signal_window_move().connect(sigc::mem_fun(*this, &MainWindow::move_to));

    container.put(calc, 0, 0);
    container.put(calc.display_hp, 115, 23);
    calc.show();
    calc.display_hp.show();
    add(container);
    container.show();
}

MainWindow::~MainWindow() {
}

bool MainWindow::move_to(double x, double y) {
    move(static_cast<int>(x), static_cast<int>(y));
}

void MainWindow::menu_show() {
#ifdef DEBUG
    if (hpDebug.is_visible())
        hpDebug.hide();
    else
        hpDebug.show();
#endif
}
