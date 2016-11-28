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

#ifndef BACKWINDOW_H_
#define BACKWINDOW_H_

#include <gtkmm.h>

#include <iostream>

#include "hpresources_external.h"
#include "signals.h"

class BackWindow : public Gtk::Window {
public:
  BackWindow(Signals *hpsignals_r);
  virtual ~BackWindow();

protected:
  bool draw_back(const Cairo::RefPtr<Cairo::Context> &cr);

  Glib::RefPtr<Gdk::Pixbuf> icon;
  Glib::RefPtr<Gdk::Pixbuf> back;
  Gtk::Image back_area;

  Signals *hpSignals;
};

#endif /* BACKWINDOW_H_ */
