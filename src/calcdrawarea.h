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

#ifndef GTKMM_CALCDRAWAREA_H
#define GTKMM_CALCDRAWAREA_H

#include "config.h"

#include <iostream>

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm.h>
#include <glibmm/fileutils.h>
#include <cairomm/context.h>

#include "hp11c.xpm"
#include "icon.xpm"
#include "core.h"
#include "keys.h"
#include "signals.h"
#include "dispdrawarea.h"

#define MENU_XS 562
#define MENU_YS 22
#define MENU_XE 600
#define MENU_YE 60

class CalcDrawArea : public Gtk::DrawingArea {
public:
    CalcDrawArea(Signals *hpsignals_r);
    virtual ~CalcDrawArea();

    DispDrawArea display_hp;

    void calc_update();

protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    virtual bool on_button_press_event(GdkEventButton *event);
    virtual bool on_button_release_event(GdkEventButton *event);

    bool button_press_draw(int keypressed);
    bool button_release_draw();

    Glib::RefPtr<Gdk::Pixbuf> calc_image;
    Cairo::RefPtr<Cairo::Context> drawing_context;

    Keys key;
    Signals *hpsignals;
};

#endif // GTKMM_CALCDRAWAREA_H
