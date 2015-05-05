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

#ifndef GTKMM_DRAWAREA_H
#define GTKMM_DRAWAREA_H

#include "config.h"

#include <iostream>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <gtkmm.h>

#include "signals.h"

#include "hp11em640.xpm"

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
    
    const int figures[128] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* ASCII characters from 0 to 31 */
        0x00000000, /* SPACE */
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, /* ASCII characters from 33 to 47 */
        0x0FFFFF0F, /* 0 */
        0x000FF000, /* 1 */
        0x00FF0FFF, /* 2 */
        0x000FFFFF, /* 3 */
        0x0F0FF0F0, /* 4 */
        0x0F00FFFF, /* 5 */
        0x0FF0FFFF, /* 6 */
        0x000FFF00, /* 7 */
        0x0FFFFFFF, /* 8 */
        0x0F0FFFFF, /* 9 */
        0,0,0,0,0,0,0, /* ASCII characters from 58 to 64 */
        0, /* A */
        0, /* B */
        0, /* C */
        0, /* D */
        0x0FF00FFF, /* E */
        0, /* F */
        0, /* G */
        0, /* H */
        0, /* I */
        0, /* J */
        0, /* K */
        0, /* L */
        0, /* M */
        0, /* N */
        0, /* O */
        0, /* P */
        0, /* Q */
        0, /* R */
        0, /* S */
        0, /* T */
        0, /* U */
        0, /* V */
        0, /* W */
        0, /* X */
        0, /* Y */
        0, /* Z */
        0,0,0,0,0,0, /* ASCII characters from 91 to 96 */
        0, /* a */
        0, /* b */
        0, /* c */
        0, /* d */
        0, /* e */
        0, /* f */
        0, /* g */
        0, /* h */
        0, /* i */
        0, /* j */
        0, /* k */
        0, /* l */
        0, /* m */
        0, /* n */
        0x00F0F0FF, /* o */
        0, /* p */
        0, /* q */
        0x00F000F0, /* r */
        0, /* s */
        0, /* t */
        0, /* u */
        0, /* v */
        0, /* w */
        0, /* x */
        0, /* y */
        0, /* z */
        0,0,0,0,0 /* ASCII characters from 123 to 127 */
    };

    string display_text = "+0.0000";

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    
    bool draw_figure(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, int segs);
    bool draw_negative(const Cairo::RefPtr<Cairo::Context>& cr);
    bool draw_display(const Cairo::RefPtr<Cairo::Context>& cr);
    bool switch_alarm(unsigned char alarm, bool state);
};

#endif
