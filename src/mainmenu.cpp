/*
 * File:   mainmenu.cpp
 * Author: giulio
 *
 * Created on 3 ottobre 2015, 14.41
 */

#include <gtkmm/stock.h>
#include <gtkmm/uimanager.h>
#include <gtkmm-2.4/gtkmm/action.h>

#include "mainmenu.h"

MainMenu::MainMenu(Signals *hpsignals_r) {
        hpsignals = hpsignals_r;

        uimanager = Gtk::UIManager::create();
        actions = Gtk::ActionGroup::create();

        actions->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT), sigc::mem_fun(*hpsignals, &Signals::sig_off_emit));
#ifdef DEBUG
        actions->add(Gtk::Action::create("ToggleDebugWindow", "Toggle Debug Window"), sigc::mem_fun(*hpsignals, &Signals::sig_debug_window_toggle_emit));
#endif
        actions->add(Gtk::Action::create("ToggleBackWindow", "Toggle Back Window"), sigc::mem_fun(*hpsignals, &Signals::sig_back_window_toggle_emit));
        actions->add(Gtk::Action::create("Reset", "Reset calculator state"), sigc::mem_fun(*hpsignals, &Signals::sig_reset_emit));

        uimanager->insert_action_group(actions);
        uimanager->add_ui_from_string(menu_main);

}

Gtk::Menu* MainMenu::GetMenu() {
        return static_cast<Gtk::Menu*>(uimanager->get_widget("/MainMenu"));
}

MainMenu::~MainMenu() {
}
