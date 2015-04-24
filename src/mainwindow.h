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
#include "icon.xpm"

#ifdef DEBUG
#include "debugwindow.h"
#endif

class MainWindow : public Gtk::Window {
public:
    MainWindow(Signals *hpsignals_r);
    virtual ~MainWindow();

protected:
    void menu_show();

    Glib::RefPtr<Gdk::Pixbuf> icon;

    CalcDrawArea calc;
    Gtk::Fixed container;
    Signals *hpsignals;

#ifdef DEBUG
    DebugWindow hpDebug;
#endif
};

#endif // GTKMM_MAINWINDOW_H
