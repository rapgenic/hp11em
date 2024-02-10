/* key.c
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
#include <string.h>

#include "key.h"

struct _Key
{
	GtkBox parent_instance;

	GtkButton *f_button;
	GtkButton *m_button;
	GtkButton *g_button;
	GtkBox    *b_button;

	int code;
};

enum {
	KEY,
	LAST_SIGNAL
};

enum {
	PROP_0,
	PROP_F_LABEL,
	PROP_M_LABEL,
	PROP_G_LABEL,
	PROP_CODE,
	LAST_PROP
};

static void key_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void key_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

static GParamSpec *props[LAST_PROP] = { NULL, };
static guint key_signals[LAST_SIGNAL] = { 0 };

G_DEFINE_TYPE (Key, key, GTK_TYPE_BOX)

static void
key_class_init (KeyClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

	gobject_class->set_property = key_set_property;
	gobject_class->get_property = key_get_property;

	props[PROP_F_LABEL] = g_param_spec_string("f-label", "F Button Label", "Text of the f-function button", "", G_PARAM_READWRITE);
	props[PROP_G_LABEL] = g_param_spec_string("g-label", "G Button Label", "Text of the g-function button", "", G_PARAM_READWRITE);
	props[PROP_M_LABEL] = g_param_spec_string("m-label", "Button Label", "Text of the main button", "", G_PARAM_READWRITE);
	props[PROP_CODE] = g_param_spec_int("code", "Emulator keycode", "Keycode passed to the emulator on click", 0, 0xFFFF, 0, G_PARAM_READWRITE);

	g_object_class_install_properties(gobject_class, LAST_PROP, props);

	key_signals[KEY] = g_signal_new("key", G_TYPE_FROM_CLASS(gobject_class), G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION, 0, NULL, NULL, NULL, G_TYPE_NONE, 2, G_TYPE_INT, G_TYPE_INT);

	gtk_widget_class_set_template_from_resource (widget_class, "/com/rapgenic/hp11em/key.ui");

	gtk_widget_class_bind_template_child (widget_class, Key, f_button);
	gtk_widget_class_bind_template_child (widget_class, Key, m_button);
	gtk_widget_class_bind_template_child (widget_class, Key, g_button);
	gtk_widget_class_bind_template_child (widget_class, Key, b_button);

	gtk_widget_class_set_css_name(widget_class, "key");
}

static void
m_button_click_cb(GtkWidget *button, gpointer data) {
	GtkButton  *m_button = GTK_BUTTON(button);
	Key *self = HP11EM_KEY(data);

	g_assert(m_button == self->m_button);

	g_signal_emit(self, key_signals[KEY], 0, KEY_KIND_M, self->code);
}

static void
key_init (Key *self)
{
	gtk_widget_init_template(GTK_WIDGET(self));

	g_signal_connect(self->m_button, "clicked", G_CALLBACK(m_button_click_cb), self);
}

static void
key_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	Key *key = HP11EM_KEY(object);

	switch (prop_id) {
		case PROP_F_LABEL:
			key_set_label(key, KEY_KIND_F, g_value_get_string(value));
			break;
		case PROP_G_LABEL:
			key_set_label(key, KEY_KIND_G, g_value_get_string(value));
			break;
		case PROP_M_LABEL:
			key_set_label(key, KEY_KIND_M, g_value_get_string(value));
			break;
		case PROP_CODE:
			key->code = g_value_get_int(value);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void
key_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	Key *key = HP11EM_KEY(object);

	switch (prop_id) {
		case PROP_F_LABEL:
			g_value_set_string(value, key_get_label(key, KEY_KIND_F));
			break;
		case PROP_G_LABEL:
			g_value_set_string(value, key_get_label(key, KEY_KIND_G));
			break;
		case PROP_M_LABEL:
			g_value_set_string(value, key_get_label(key, KEY_KIND_M));
			break;
		case PROP_CODE:
			g_value_set_int(value, key->code);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

void
key_set_label (Key *key, KeyKind kind, const char *label)
{
	g_return_if_fail (HP11EM_IS_KEY (key));

	GtkStyleContext *box_style = gtk_widget_get_style_context(GTK_WIDGET(key->b_button));
	GtkStyleContext *m_style = gtk_widget_get_style_context(GTK_WIDGET(key->m_button));
	GtkStyleContext *g_style = gtk_widget_get_style_context(GTK_WIDGET(key->g_button));

	switch (kind) {
		case KEY_KIND_F:
			gtk_button_set_label (key->f_button, label);
			break;
		case KEY_KIND_G:
			// If G label is not present do not draw the button in linked mode
			// as there is only one
			if (label)
				gtk_style_context_add_class(box_style, "linked");
			else
			 	gtk_style_context_remove_class(box_style, "linked");

			// If G label is present but empty, then it's a special button, so
			// add the opaque class
			if (label && !strcmp(label, "")) {
				gtk_style_context_add_class(m_style, "opaque");
				gtk_style_context_add_class(g_style, "opaque");
			} else {
				gtk_style_context_remove_class(m_style, "opaque");
				gtk_style_context_remove_class(g_style, "opaque");
			}

			gtk_button_set_label (key->g_button, label);
			break;
		case KEY_KIND_M:
			gtk_button_set_label (key->m_button, label);
			break;
	}
}

const char *
key_get_label (Key *key, KeyKind kind)
{
	g_return_val_if_fail (HP11EM_IS_KEY (key), NULL);

	switch (kind) {
		case KEY_KIND_F:
			return gtk_button_get_label(key->f_button);
			break;
		case KEY_KIND_M:
			return gtk_button_get_label(key->m_button);
			break;
		case KEY_KIND_G:
			return gtk_button_get_label(key->g_button);
			break;
	}

	return NULL;
}