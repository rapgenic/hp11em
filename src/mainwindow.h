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

#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include "config.h"

#include <iostream>

#include <gdkmm/pixbuf.h>
#include <gtkmm/fixed.h>
#include <gtkmm/window.h>

#include "calcdrawarea.h"
#include "core.h"
#include "hpresources_external.h"
#include "signals.h"

#ifdef DEBUG
#include "debugwindow.h"
#endif

class MainWindow : public Gtk::Window {
public:
  MainWindow(Signals *hpsignals_r);
  virtual ~MainWindow();

protected:
  void debug_window_show();
  bool on_back_area_button_press_event(GdkEventButton *event);
  void toggle_front_back();
  bool on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr) override;

  Glib::RefPtr<Gdk::Pixbuf> icon;
  Glib::RefPtr<Gdk::Pixbuf> back;
  
  CalcDrawArea calc;
  Gtk::Image backArea;  
  Gtk::EventBox backAreaEvBox;  
  Gtk::Fixed container;
  Signals *hpsignals;

#ifdef DEBUG
  DebugWindow hpDebug;
#endif
};

#endif // GTKMM_MAINWINDOW_H
