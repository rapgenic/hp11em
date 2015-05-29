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

#include <iostream>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <gtkmm.h>

#include "signals.h"
#include "dispdrawarea.h"

DispDrawArea::DispDrawArea(Signals *hpsignals_r) {
    hpsignals = hpsignals_r;

    set_events(Gdk::KEY_PRESS_MASK);
    add_events(Gdk::KEY_RELEASE_MASK);

    hpsignals->signal_alarm().connect(sigc::mem_fun(*this, &DispDrawArea::switch_alarm));
    hpsignals->signal_display().connect(sigc::mem_fun(*this, &DispDrawArea::display_write));

    hp_image = Gdk::Pixbuf::create_from_xpm_data(hp11em640_xpm);

    // Maybe we don't have to do it, just create a rectangle with cairo
    // and fill it with DISP_BG; needs further check -> replaced with a
    // RECTANGLE
    //
    // display_hp = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB,false,8,300,40+15);
    // display_hp->fill(0?DISP_BG:0xFFFFFFFF);

    // Preparing the alarms' PixBufs
    alarms[A_000] = Gdk::Pixbuf::create_subpixbuf(hp_image, 0, 382, 17, 11);
    alarms[A_SDF] = Gdk::Pixbuf::create_subpixbuf(hp_image, 18, 382, 20, 11);
    alarms[A_002] = Gdk::Pixbuf::create_subpixbuf(hp_image, 39, 382, 22, 11);
    alarms[A_003] = Gdk::Pixbuf::create_subpixbuf(hp_image, 62, 382, 15, 12);
    alarms[A_BAT] = Gdk::Pixbuf::create_subpixbuf(hp_image, 78, 385, 20, 10);
    alarms[A_GRD] = Gdk::Pixbuf::create_subpixbuf(hp_image, 99, 384, 5, 10);
    alarms[A_RAD] = Gdk::Pixbuf::create_subpixbuf(hp_image, 104, 384, 14, 10);

    set_size_request(300, 40 + 15);
}

DispDrawArea::~DispDrawArea() {
}

bool DispDrawArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // IMPORTANT
    // decided to use this callback to write the display, so call this
    // whenever there is something to draw and implement here all the
    // drawing system
    // IMPORTANT

    // Paints the display
    // Gdk::Cairo::set_source_pixbuf(cr, display_hp, 0, 0);
    cr->set_source_rgb(static_cast<double> ((DISP_BG & 0xFF000000) >> 24) / 255, static_cast<double> ((DISP_BG & 0x00FF0000) >> 16) / 255, static_cast<double> ((DISP_BG & 0x0000FF00) >> 8) / 255);
    cr->rectangle(0.0, 0.0, 300.0, 40.0 + 15.0);
    cr->fill();
    cr->paint();

    // Draws the alarms
    for (int i = 0; i < 7; i++) {
        if (alarms_state[i]) {
            Gdk::Cairo::set_source_pixbuf(cr, alarms[i], alarm_pos[i][0], alarm_pos[i][1]);
            cr->paint();
        }
    }

    // Draws the display
    draw_display(cr);

    return true;
}

bool DispDrawArea::draw_figure(const Cairo::RefPtr<Cairo::Context>& cr, int x, int y, int segs) {
    // Limit the drawing position
    x += 28;

    // Setting up the context
    // TBD correct color
    cr->set_source_rgb(0, 0, 0);
    cr->set_line_width(3);
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    // Drawing 1st segment
    if ((segs & 0x0F000000) >> 24) {
        cr->move_to(x, y);
        cr->line_to(x - 1, y + 8);
        cr->stroke();
    }

    // drawing 2nd segment
    if ((segs & 0x00F00000) >> 20) {
        cr->move_to(x - 1, y + 11);
        cr->line_to(x - 2, y + 19);
        cr->stroke();
    }

    // drawing 3rd segment
    if ((segs & 0x000F0000) >> 16) {
        cr->move_to(x + 11, y);
        cr->line_to(x + 11 - 1, y + 8);
        cr->stroke();
    }

    // drawing 4th segment
    if ((segs & 0x0000F000) >> 12) {
        cr->move_to(x + 11 - 1, y + 11);
        cr->line_to(x + 11 - 2, y + 19);
        cr->stroke();
    }

    // drawing 5th segment
    if ((segs & 0x00000F00) >> 8) {
        cr->move_to(x + 3, y - 2);
        cr->line_to(x + 3 + 5, y - 2);
        cr->stroke();
    }

    // drawing 6th segment
    if ((segs & 0x000000F0) >> 4) {
        cr->move_to(x + 3 - 1, y - 2 + 12);
        cr->line_to(x + 3 + 5 - 1, y - 2 + 12);
        cr->stroke();
    }

    // drawing 7th segment
    if ((segs & 0x0000000F)) {
        cr->move_to(x + 3 - 2, y - 2 + 23);
        cr->line_to(x + 3 + 5 - 2, y - 2 + 23);
        cr->stroke();
    }

    // drawing the comma / dot
    if (((segs & 0xF0000000) >> 28) > 0x9) {
        cr->rectangle(x + 14, y + 20, 1, 1);
        cr->stroke();
        if (((segs & 0xF0000000) >> 28) == 0xF) {
            cr->rectangle(x + 14, y + 24, 0.5, 1);
            cr->stroke();
        }
    }

    return true;
}

bool DispDrawArea::draw_display(const Cairo::RefPtr<Cairo::Context>& cr) {
    int i = 1, z = 0;

    if (display_text[0] == 'E') {

        // printing error message
        draw_figure(cr, (DISP_FIG_WIDTH * 1 + DISP_FIG_DIST * 1), DISP_FIG_Y, figures['E']);
        draw_figure(cr, (DISP_FIG_WIDTH * 2 + DISP_FIG_DIST * 2), DISP_FIG_Y, figures['r']);
        draw_figure(cr, (DISP_FIG_WIDTH * 3 + DISP_FIG_DIST * 3), DISP_FIG_Y, figures['r']);
        draw_figure(cr, (DISP_FIG_WIDTH * 4 + DISP_FIG_DIST * 4), DISP_FIG_Y, figures['o']);
        draw_figure(cr, (DISP_FIG_WIDTH * 5 + DISP_FIG_DIST * 5), DISP_FIG_Y, figures['r']);
        draw_figure(cr, (DISP_FIG_WIDTH * 7 + DISP_FIG_DIST * 7), DISP_FIG_Y, figures[display_text[5]]);

        return true;
    }

    if (display_text[0] == '-')
        draw_negative(cr);

    while (i < 22) {
        int figure = 0;

        if (display_text[i] == '\0')
            break;

        figure = figures[display_text[i]];

        if (display_text[i + 1] == '.')
            figure |= 0xA0000000;
        else if (display_text[i + 1] == ',')
            figure |= 0xF0000000;

        draw_figure(cr, (DISP_FIG_WIDTH * z + DISP_FIG_DIST * z), DISP_FIG_Y, figure);

        if (display_text[i + 1] == '.' || display_text[i + 1] == ',')
            i++;

        z++;

        i++;

        if (z > 9)
            break;
    }

    return true;
}

bool DispDrawArea::draw_negative(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Setting up the context
    // TBD correct color
    cr->set_source_rgb(0, 0, 0);
    cr->set_line_width(3);
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    // drawing the negative sign
    cr->move_to(5, DISP_FIG_Y + 10);
    cr->line_to(12, DISP_FIG_Y + 10);
    cr->stroke();

    return true;
}

bool DispDrawArea::display_update() {
    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();

    if (!on_draw(cr))
        return false;

    return true;
}

bool DispDrawArea::switch_alarm(unsigned char alarm, bool state) {
    // Activates or deactivates the alarm passed by the signal
    alarms_state[alarm] = state;

    // Writes the changes
    if (!display_update())
        return false;

    return true;
}

bool DispDrawArea::display_write(string r_text) {
    r_text.resize(22);
    display_text = r_text;

    if (!display_update())
        return false;

    return true;
}
