#include <gtkmm/application.h>

#include <iostream>
using namespace std;

#include "config.h"
#include "signals.h"
#include "core.h"
#include "mainwindow.h"

// <<TBD>> create a new hp11c image and check the buttons' position

int main(int argc, char *argv[]) {
#ifdef DEBUG
    cout << "Creating GTKMM application..." << endl << flush;
#endif
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.hp11c.emulator");

    // creates a signal handler to exchange data from the core to the GUI
#ifdef DEBUG
    cout << "Starting the signal handler..." << endl << flush;
#endif
    Signals hpSignals;

    // creates the core
#ifdef DEBUG
    cout << "Starting the core..." << endl << flush;
#endif
    Core hpCore(&hpSignals);

    // creates the user interface
#ifdef DEBUG
    cout << "Starting the GUI..." << endl << flush;
#endif
    MainWindow hpMainWindow(&hpSignals);

    //Shows the window and returns when it is closed.
#ifdef DEBUG
    cout << "Starting GTKMM application..." << endl << flush;
#endif
    return app->run(hpMainWindow);
}
