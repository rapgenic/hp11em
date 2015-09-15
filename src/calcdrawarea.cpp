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

#include "calcdrawarea.h"

CalcDrawArea::CalcDrawArea(Signals *hpsignals_r)
: display_hp(hpsignals_r) {
    hpsignals = hpsignals_r;

    calc_image = Gdk::Pixbuf::create_from_xpm_data(hp11em640_xpm);

    set_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);
    add_events(Gdk::BUTTON_MOTION_MASK);
    add_events(Gdk::KEY_PRESS_MASK);
    add_events(Gdk::KEY_RELEASE_MASK);

    set_can_focus(true);
    grab_focus();

    if (calc_image)
        set_size_request(640, 382);

    last_x = last_y = 0;
}

CalcDrawArea::~CalcDrawArea() {
}

bool CalcDrawArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Draws the calculator's image
    if (!calc_image)
        return false;

    Gdk::Cairo::set_source_pixbuf(cr, calc_image, 0, 0);
    cr->paint();

    return true;
}

bool CalcDrawArea::on_motion_notify_event(GdkEventMotion *event) {
    //    if (0 <= event->x && event->x <= 640 && 0 <= event->y && event->y <= 100 && event->x < MENU_XS && event->x > MENU_XE && event->y < MENU_YS && event->y > MENU_YE) {
    if (((event->x >= 0 && event->x < MENU_XS) || (event->x > MENU_XE && event->x <= 640)) && ((event->y >= 0 && event->y < MENU_YS) || (event->y > MENU_YE && event->y <= 100))) {
        hpsignals->sig_window_move_emit(event->x_root - event->x + (event->x_root - last_x), event->y_root - event->y + (event->y_root - last_y));
        last_x = event->x_root;
        last_y = event->y_root;
    }
}

bool CalcDrawArea::on_button_press_event(GdkEventButton *event) {
#ifdef DEBUG
    cerr << endl;
#endif

    int keypressed;

    last_x = event->x_root;
    last_y = event->y_root;

    for (keypressed = 0; keypressed < KEY_NUMBER; keypressed++)
        if ((key.key_location[keypressed][0] <= (int) event->x) && (key.key_location[keypressed][2] >= (int) event->x) && (key.key_location[keypressed][1] <= (int) event->y) && (key.key_location[keypressed][3] >= (int) event->y))
            break;

#ifdef DEBUG
    std::cerr << KBLU << "Key Pressed: X = " << event->x << "; Y = " << event->y << KRST << std::endl << std::flush;
#endif

    if (keypressed == 39) {
        if ((MENU_XS <= (int) event->x) && (MENU_XE >= (int) event->x) && (MENU_YS <= (int) event->y) && (MENU_YE >= (int) event->y)) {
            if (event->type == GDK_BUTTON_PRESS) {
#ifdef DEBUG
                std::cerr << KBLU << "Pressed Menu Key" << KRST << std::endl << std::flush;
#endif
                hpsignals->sig_menu_emit();
                return true;
            }
        } else {
            if (event->type == GDK_2BUTTON_PRESS) {
#ifdef DEBUG
                std::cerr << KBLU << "Pressed Minimize Key" << KRST << std::endl << std::flush;
#endif                
                hpsignals->sig_minimize_emit();
            }
        }
    } else {
        if (event->type == GDK_BUTTON_PRESS) {
            hpsignals->sig_key_emit(keypressed);
            button_press_draw(keypressed);
        }
    }

    return true;
}

bool CalcDrawArea::on_button_release_event(GdkEventButton *event) {
    // Updates the window to release buttons
    // We have to update also the display to keep its content
    button_release_draw();

    return true;
}

bool CalcDrawArea::on_key_press_event(GdkEventKey* event) {
#ifdef DEBUG
    cerr << endl;
    cerr << KBLU << "Keyboard Pressed: " << event->keyval << KRST << endl;
#endif

    parse_numpad(event);
    
    if (event->type == GDK_KEY_PRESS) {
        for (int keypressed = 0; keypressed < KEY_NUMBER; keypressed++) {
            if (key.keycodes[keypressed] == event->keyval) {
                if ((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_CONTROL_MASK) {
                    hpsignals->sig_key_emit(Keys::K_SDF);
#ifdef DEBUG
                    cerr << endl;
                    cerr << KBLU << "Ctrl (F) modifier" << KRST << endl;
#endif
                } else if ((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_MOD1_MASK) {
                    hpsignals->sig_key_emit(Keys::K_GDF);
#ifdef DEBUG
                    cerr << endl;
                    cerr << KBLU << "Alt (G) modifier" << KRST << endl;
#endif
                }

                hpsignals->sig_key_emit(keypressed);
                button_press_draw(keypressed);
            }
        }
    }

    return true;
}

void CalcDrawArea::parse_numpad(GdkEventKey* event) {
    switch (event->keyval) {
        case GDK_KEY_KP_0:
            event->keyval = GDK_KEY_0;
            break;
        case GDK_KEY_KP_1:
            event->keyval = GDK_KEY_1;
            break;
        case GDK_KEY_KP_2:
            event->keyval = GDK_KEY_2;
            break;
        case GDK_KEY_KP_3:
            event->keyval = GDK_KEY_3;
            break;
        case GDK_KEY_KP_4:
            event->keyval = GDK_KEY_4;
            break;
        case GDK_KEY_KP_5:
            event->keyval = GDK_KEY_5;
            break;
        case GDK_KEY_KP_6:
            event->keyval = GDK_KEY_6;
            break;
        case GDK_KEY_KP_7:
            event->keyval = GDK_KEY_7;
            break;
        case GDK_KEY_KP_8:
            event->keyval = GDK_KEY_8;
            break;
        case GDK_KEY_KP_9:
            event->keyval = GDK_KEY_9;
            break;
        case GDK_KEY_KP_Enter: 
            event->keyval = GDK_KEY_Return;
            break;
        case GDK_KEY_KP_Add:
            event->keyval = GDK_KEY_plus;
            break;
        case GDK_KEY_KP_Subtract:
            event->keyval = GDK_KEY_minus;
            break;
        case GDK_KEY_KP_Multiply:
            event->keyval = GDK_KEY_asterisk;
            break;
        case GDK_KEY_KP_Divide:
            event->keyval = GDK_KEY_slash;
            break;
        case GDK_KEY_KP_Decimal:
            event->keyval = GDK_KEY_period;
            break;
    }
}

bool CalcDrawArea::on_key_release_event(GdkEventKey* event) {
    button_release_draw();

    return true;
}

bool CalcDrawArea::button_release_draw() {
    // Redraws the whole window
    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    on_draw(cr);

    display_hp.display_update();

    return true;
}

bool CalcDrawArea::button_press_draw(int keypressed) {
    Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
    Glib::RefPtr<Gdk::Pixbuf> button = Gdk::Pixbuf::create_subpixbuf(calc_image, key.key_location[keypressed][0], key.key_location[keypressed][1], key.key_location[keypressed][2] - key.key_location[keypressed][0], key.key_location[keypressed][3] - key.key_location[keypressed][1]);

    cr->save();

    Gdk::Cairo::set_source_pixbuf(cr, button, key.key_location[keypressed][0] + 1, key.key_location[keypressed][1] + 1);
    cr->paint();

    cr->restore();

    return true;
}
