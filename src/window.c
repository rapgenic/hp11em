/* window.c
 *
 * Copyright 2022 Giulio Girardi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <adwaita.h>
#include <stdio.h>

#include "window.h"
#include "key.h"

struct _Window
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  // GtkHeaderBar        *header_bar;
  // GtkLabel            *label;
  GtkGrid *keypad;
};

G_DEFINE_TYPE (Window, window, GTK_TYPE_APPLICATION_WINDOW)

static void
key_pressed(GtkWidget *window, KeyKind kind, int code) {
  Window *self = HP11EM_WINDOW(window);

  printf("Kind: %d, code %d\n", kind, code);
}

static void
window_class_init (WindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/com/rapgenic/hp11em/window.ui");
  gtk_widget_class_bind_template_child (widget_class, Window, keypad);
  gtk_widget_class_bind_template_callback (widget_class, key_pressed);
}

static void
window_init (Window *self)
{
  AdwStyleManager *manager = adw_style_manager_get_default();

  gtk_widget_init_template (GTK_WIDGET (self));

  adw_style_manager_set_color_scheme(manager, ADW_COLOR_SCHEME_FORCE_DARK);
}
