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

MainWindow::MainWindow(Signals *hpsignals_r)
    : calc(hpsignals_r)
#ifdef DEBUG
      , hpDebug(hpsignals_r)
#endif
  {
  // Register resources
  resources_register_resource();

  // creates the user interface
  hpsignals = hpsignals_r;

  try {
    /*
     * Sadly I can't use Gdk::Pixbuf::create_from_resource() because it's
     * available only in 3.12+
     */

    GError *error = NULL;

    icon = Gdk::Pixbuf::create_from_stream(Glib::wrap(g_resource_open_stream(resources_get_resource(), "/com/rapgenic/hp11em/images/icon.svg", G_RESOURCE_LOOKUP_FLAGS_NONE, &error)));
    back = Gdk::Pixbuf::create_from_stream(Glib::wrap(g_resource_open_stream(resources_get_resource(), "/com/rapgenic/hp11em/images/back.png", G_RESOURCE_LOOKUP_FLAGS_NONE, &error)));
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << KRED << "PixbufError: " << ex.what() << KRST << std::endl;
  }

  set_icon(icon);
  set_resizable(false);
  set_decorated(false);

  hpsignals->signal_off().connect(sigc::mem_fun(*this, &MainWindow::hide));
  hpsignals->signal_minimize().connect(sigc::mem_fun(*this, &MainWindow::iconify));
#ifdef DEBUG
  hpsignals->signal_debug_window_toggle().connect(sigc::mem_fun(*this, &MainWindow::debug_window_show));
#endif
  hpsignals->signal_back_window_toggle().connect(sigc::mem_fun(*this, &MainWindow::toggle_front_back));
  hpsignals->signal_window_move().connect(sigc::mem_fun(*this, &MainWindow::move));
  hpsignals->signal_window_begin_move_drag().connect(sigc::mem_fun(*this, &MainWindow::begin_move_drag));

  backArea.set(back);

  backAreaEvBox.add(backArea);
  backAreaEvBox.set_events(Gdk::BUTTON_PRESS_MASK);
  backAreaEvBox.signal_button_press_event().connect(sigc::mem_fun(*this, &MainWindow::on_back_area_button_press_event));

  container.put(calc, 0, 0);
  container.put(calc.display_hp, 119, 23);
  container.put(backAreaEvBox, 0, 0);

  calc.show();
  calc.display_hp.show();

  add(container);
  container.show();
}

MainWindow::~MainWindow() { resources_unregister_resource(); }

bool MainWindow::on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr) {
  hpsignals->sig_gui_ready_emit();
  return Gtk::Window::on_draw(cr);
}

bool MainWindow::on_back_area_button_press_event(GdkEventButton *event) {
  toggle_front_back();
}

void MainWindow::toggle_front_back() {
  if (calc.is_visible()) {
    calc.hide();
    calc.display_hp.hide();
    backArea.show();
    backAreaEvBox.show();
  } else {
    calc.show();
    calc.display_hp.show();    
    backArea.hide();
    backAreaEvBox.hide();
  }
}

#ifdef DEBUG
void MainWindow::debug_window_show() {
  if (hpDebug.is_visible())
    hpDebug.hide();
  else
    hpDebug.show();
}
#endif
