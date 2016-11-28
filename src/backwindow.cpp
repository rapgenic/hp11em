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

#include "backwindow.h"

BackWindow::BackWindow(Signals *hpsignals_r) {
  try {
    /*
     * Sadly I can't use Gdk::Pixbuf::create_from_resource() because it's
     * available only in 3.12+
     */

    GError *error = NULL;

    icon = Gdk::Pixbuf::create_from_stream(Glib::wrap(g_resource_open_stream(
        resources_get_resource(), "/com/rapgenic/hp11em/images/icon.svg",
        G_RESOURCE_LOOKUP_FLAGS_NONE, &error)));
    back = Gdk::Pixbuf::create_from_stream(Glib::wrap(g_resource_open_stream(
        resources_get_resource(), "/com/rapgenic/hp11em/images/back.png",
        G_RESOURCE_LOOKUP_FLAGS_NONE, &error)));
  } catch (const Gdk::PixbufError &ex) {
    std::cerr << "PixbufError: " << ex.what() << std::endl;
  }

  set_icon(icon);
  set_resizable(false);
  set_can_focus(true);
  set_title("Back view");
  grab_focus();

  hpSignals = hpsignals_r;

  hpSignals->signal_off().connect(sigc::mem_fun(*this, &BackWindow::hide));

  if (back)
    back_area.set_size_request(640, 382);

  back_area.set(back);
  back_area.show();

  add(back_area);
}

BackWindow::~BackWindow() {}
