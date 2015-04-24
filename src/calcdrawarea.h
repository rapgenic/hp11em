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
