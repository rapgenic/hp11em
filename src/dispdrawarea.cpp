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

#include "dispdrawarea.h"

// <<TBD>> write the text system for the display
// <<TDB>> correct the alarms

DispDrawArea::DispDrawArea(Signals *hpsignals_r) {
    hpsignals = hpsignals_r;

    set_events(Gdk::KEY_PRESS_MASK);
    add_events(Gdk::KEY_RELEASE_MASK);

    hpsignals->signal_alarm().connect(sigc::mem_fun(*this, &DispDrawArea::switch_alarm));
    hpsignals->signal_display().connect(sigc::mem_fun(*this, &DispDrawArea::display_write));

    hp_image = Gdk::Pixbuf::create_from_xpm_data(hp11c_xpm);

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

bool DispDrawArea::draw_display(const Cairo::RefPtr<Cairo::Context>& cr) {
    Pango::FontDescription font;

    font.set_family("HP15C Simulator Font");
    font.set_absolute_size(40*PANGO_SCALE);

    Glib::RefPtr<Pango::Layout> layout = create_pango_layout(display_text);

    layout->set_font_description(font);

    // Position the text
    cr->move_to(8, 4);
    cr->set_source_rgb(0.0, 0.0, 0.0);

    layout->show_in_cairo_context(cr);

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
