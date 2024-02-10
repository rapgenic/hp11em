/* application.c
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

#include "application.h"

#include <adwaita.h>
#include <stdbool.h>
#include <unistd.h>

#include "window.h"
#include "key.h"
#include "nonpareil/display.h"
#include "nonpareil/model.h"
#include "nonpareil/proc.h"
#include "nonpareil/util.h"

struct _Application
{
  AdwApplication parent_instance;

  sim_t *sim;
};

G_DEFINE_TYPE (Application, application, ADW_TYPE_APPLICATION)

static void application_display_update (ApplicationClass *klass, int digit_count, segment_bitmap_t *segments);

Application *
application_new (gchar *application_id,
                        GApplicationFlags  flags)
{
  Application *self = g_object_new (TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);

  int model = find_model_by_name("11C");
  model_info_t *model_info = get_model_info(model);

  self->sim = sim_init(
    self,
    model,
    model_info->clock_frequency,
    model_info->ram_size,
    NULL,
    0, // This would be an error, except that for this model it's not used
    (display_update_callback_fn_t *) &application_display_update
  );

  return self;
}

static void
application_finalize (GObject *object)
{
  Application *self = (Application *)object;

  sim_quit(self->sim);

  G_OBJECT_CLASS (application_parent_class)->finalize (object);
}

static void
application_activate (GApplication *_app)
{
  GtkWindow *window;
  Application *app = HP11EM_APPLICATION(_app);

  /* It's good practice to check your parameters at the beginning of the
   * function. It helps catch errors early and in development instead of
   * by your users.
   */
  g_assert (HP11EM_IS_APPLICATION (app));

  key_get_type();

  /* Get the current window or create one if necessary. */
  window = gtk_application_get_active_window (GTK_APPLICATION (app));
  if (window == NULL)
    window = g_object_new (TYPE_WINDOW,
                           "application", app,
                           "default-width", 600,
                           "default-height", 300,
                           NULL);

  /* Ask the window manager/compositor to present the window. */
  gtk_window_present (window);

  /* Start the simulator */
  if (sim_read_object_file(app->sim, "11c.obj"))
  {
    sim_reset(app->sim);
    sim_start(app->sim);
  }
}


static void
application_class_init (ApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = application_finalize;

  /*
   * We connect to the activate callback to create a window when the application
   * has been launched. Additionally, this callback notifies us when the user
   * tries to launch a "second instance" of the application. When they try
   * to do that, we'll just present any existing window.
   */
  app_class->activate = application_activate;
}

static void
application_display_update (ApplicationClass *klass,
                                   int digit_count,
                                   segment_bitmap_t *segments)
{
  printf("Digit count: %d\n", digit_count);
}

static void
application_show_about (GSimpleAction *action,
                               GVariant      *parameter,
                               gpointer       user_data)
{
  Application *self = HP11EM_APPLICATION (user_data);
  GtkWindow *window = NULL;
  const gchar *authors[] = {"Giulio Girardi", NULL};

  g_return_if_fail (HP11EM_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  gtk_show_about_dialog (window,
                         "program-name", "hp11em",
                         "authors", authors,
                         "version", "0.1.0",
                         NULL);
}


static void
application_init (Application *self)
{
  GSimpleAction *quit_action = g_simple_action_new ("quit", NULL);
  g_signal_connect_swapped (quit_action, "activate", G_CALLBACK (g_application_quit), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (quit_action));

  GSimpleAction *about_action = g_simple_action_new ("about", NULL);
  g_signal_connect (about_action, "activate", G_CALLBACK (application_show_about), self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (about_action));

  const char *accels[] = {"<primary>q", NULL};
  gtk_application_set_accels_for_action (GTK_APPLICATION (self), "app.quit", accels);
}
