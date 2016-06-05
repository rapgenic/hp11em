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

#include <gtkmm/window.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/fixed.h>

#include "calcdrawarea.h"
#include "core.h"
#include "signals.h"
#include "hpresources_external.h"
#include "backwindow.h"

#ifdef DEBUG
#include "debugwindow.h"
#endif

class MainWindow: public Gtk::Window {
public:
        MainWindow(Signals *hpsignals_r);
        virtual ~MainWindow();

protected:
        void debug_window_show();
        void back_window_show();
        bool move_to(double x, double y);
        bool on_draw(const ::Cairo::RefPtr<::Cairo::Context>& cr) override;

        Glib::RefPtr<Gdk::Pixbuf> icon;

        CalcDrawArea calc;
        Gtk::Fixed container;
        Signals *hpsignals;

        BackWindow hpBack;
#ifdef DEBUG
        DebugWindow hpDebug;
#endif
};

#endif // GTKMM_MAINWINDOW_H
