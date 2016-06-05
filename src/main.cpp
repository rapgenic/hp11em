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

#include <gtkmm/application.h>

#include <iostream>
using std::cerr;
using std::endl;
using std::flush;

#include "config.h"
#include "signals.h"
#include "core.h"
#include "mainwindow.h"
#include "colors.h"

// <<TBD>> create a new hp11c image and check the buttons' position

int main(int argc, char *argv[]) {
#ifdef DEBUG
        cerr << KGRN << "Creating GTKMM application..." << KRST << endl << flush;
#endif
        Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.rapgenic.hp11em");

        // creates a signal handler to exchange data from the core to the GUI
#ifdef DEBUG
        cerr << KGRN << "Starting the signal handler..." << KRST << endl << flush;
#endif
        Signals hpSignals;

        // creates the core
#ifdef DEBUG
        cerr << KGRN << "Starting the core..." << KRST << endl << flush;
#endif
        Core hpCore(&hpSignals);

        // creates the user interface
#ifdef DEBUG
        cerr << KGRN << "Starting the GUI..." << KRST << endl << flush;
#endif
        MainWindow hpMainWindow(&hpSignals);

        //Shows the window and returns when it is closed.
#ifdef DEBUG
        cerr << KGRN << "Starting GTKMM application..." << KRST << endl << flush;
#endif
        return app->run(hpMainWindow);
}
