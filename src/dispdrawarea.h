#ifndef GTKMM_DRAWAREA_H
#define GTKMM_DRAWAREA_H

#include "config.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <gtkmm/drawingarea.h>
#include <gdkmm/pixbuf.h>
#include <gdkmm.h>
#include <glibmm/fileutils.h>
#include <cairomm/context.h>

#include "signals.h"
#include "hp11c.xpm"

#define DISP_BG 0x6D8269FF
#define DISP_FIG_WIDTH 15
#define DISP_FIG_DIST 12
#define DISP_FIG_Y 20

#define A_000 0
#define A_SDF 1
#define A_002 2
#define A_003 3
#define A_BAT 4
#define A_GRD 5
#define A_RAD 6
#define A_GDF 7
#define A_008 8
#define A_009 9

class DispDrawArea : public Gtk::DrawingArea {
public:
    typedef char alarm_t;

    DispDrawArea(Signals *hpsignals_r);
    virtual ~DispDrawArea();

    bool display_update();
    bool display_write(string r_text);

protected:
    Glib::RefPtr<Gdk::Pixbuf> hp_image;
    Glib::RefPtr<Gdk::Pixbuf> alarms[7];

    Signals *hpsignals;

    bool alarms_state[7] = {0, 0, 0, 0, 0, 0, 0};
    const char alarm_pos[10][4] = {
        {3, 0, 17, 11},
        {24, 0, 20, 11},
        {47, 0, 22, 11},
        {72, 0, 15, 12},
        {90, 2, 20, 10},
        {113, 1, 5, 10},
        {118, 1, 14, 10},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    string display_text = "+0.000";

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool draw_figure(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, int segs);
    bool draw_negative(const Cairo::RefPtr<Cairo::Context>& cr);
    bool draw_display(const Cairo::RefPtr<Cairo::Context>& cr);
    bool switch_alarm(unsigned char alarm, bool state);
};

#endif
