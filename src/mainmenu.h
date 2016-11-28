/*
 * File:   mainmenu.h
 * Author: giulio
 *
 * Created on 3 ottobre 2015, 14.41
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "config.h"

#include <gtkmm/action.h>
#include <gtkmm/menu.h>
using Gtk::ActionGroup;
using Gtk::Action;

#include "signals.h"

class MainMenu : Gtk::Menu {
public:
  MainMenu(Signals *hpsignals_r);
  Gtk::Menu *GetMenu();

  virtual ~MainMenu();

private:
  Signals *hpsignals;

  Glib::RefPtr<Gtk::UIManager> uimanager;
  Glib::RefPtr<ActionGroup> actions;

  Glib::ustring menu_main = "<ui>"
                            "   <popup name='MainMenu'>"
#ifdef DEBUG
                            "       <menuitem action='ToggleDebugWindow' />"
#endif
                            "       <menuitem action='ToggleBackWindow' />"
                            "       <separator />"
                            "       <menuitem action='Reset' />"
                            "       <separator />"
                            "       <menuitem action='Quit' />"
                            "   </popup>"
                            "</ui>";
};

#endif /* MAINMENU_H */
