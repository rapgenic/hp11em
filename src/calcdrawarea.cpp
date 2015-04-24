#include "calcdrawarea.h"

CalcDrawArea::CalcDrawArea(Signals *hpsignals_r)
: display_hp(hpsignals_r) {
    hpsignals = hpsignals_r;

    calc_image = Gdk::Pixbuf::create_from_xpm_data(hp11c_xpm);

    set_events(Gdk::BUTTON_PRESS_MASK);
    add_events(Gdk::BUTTON_RELEASE_MASK);

    if (calc_image)
        set_size_request(640, 382);
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

bool CalcDrawArea::on_button_press_event(GdkEventButton *event) {
    int keypressed;

    for (keypressed = 0; keypressed < 39; keypressed++)
        if ((key.key_location[keypressed][0] <= (int) event->x) && (key.key_location[keypressed][2] >= (int) event->x) && (key.key_location[keypressed][1] <= (int) event->y) && (key.key_location[keypressed][3] >= (int) event->y))
            break;

#ifdef DEBUG
    std::cout << "Key Pressed: X = " << event->x << "; Y = " << event->y << std::endl << std::flush;
#endif

    if (keypressed == 39) {
        if ((MENU_XS <= (int) event->x) && (MENU_XE >= (int) event->x) && (MENU_YS <= (int) event->y) && (MENU_YE >= (int) event->y)) {
#ifdef DEBUG
            std::cout << "Pressed Menu Key" << std::endl << std::flush;
#endif
            hpsignals->sig_menu_emit();
            return true;
        } else {
            keypressed = -1;
        }
    } else {
        button_press_draw(keypressed);
    }

    hpsignals->sig_key_emit(keypressed);

    return true;
}

bool CalcDrawArea::on_button_release_event(GdkEventButton *event) {
    // Updates the window to release buttons
    // We have to update also the display to keep its content
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
