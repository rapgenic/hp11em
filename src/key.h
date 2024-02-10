/* key.h
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

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define TYPE_KEY (key_get_type())

G_DECLARE_FINAL_TYPE (Key, key, HP11EM, KEY, GtkBox)

typedef enum
{
  KEY_KIND_F,
  KEY_KIND_M,
  KEY_KIND_G,
} KeyKind;

void key_set_label (Key *key, KeyKind kind, const char *label);
const char *key_get_label (Key *key, KeyKind kind);

G_END_DECLS
