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

#include "colors.h"
#include "hpresources_external.h"
#include "signals.h"

#define DISP_BG 0x718464FF
#define DISP_FIG_WIDTH 15
#define DISP_FIG_DIST 12
#define DISP_FIG_Y 18

#define A_USR 0
#define A_SDF 1
#define A_GDF 2
#define A_BGN 3
#define A_GRD 4
#define A_RAD 5
#define A_DMY 6
#define A_CCC 7
#define A_PRG 8

class DispDrawArea : public Gtk::DrawingArea {
public:
  typedef char alarm_t;

  DispDrawArea(Signals *hpsignals_r);
  virtual ~DispDrawArea();

  bool display_update();
  bool display_write(string r_text);

protected:
  Glib::RefPtr<Gdk::Pixbuf> hp_image;
  Glib::RefPtr<Gdk::Pixbuf> alarms[9];

  Signals *hpsignals;

  bool alarms_state[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  const int alarm_pos[9][4] = {
      {3, 42, 17, 13},   {41, 42, 20, 13},  {57, 42, 22, 13},
      {73, 42, 15, 13},  {121, 42, 20, 13}, {133, 42, 5, 13},
      {162, 42, 14, 13}, {202, 42, 0, 13},  {218, 42, 0, 13}};

  const int
      figures
          [128] =
              {
                  0,          0,          0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0,          0,          0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0,          0,          0, 0, 0, 0, 0, 0, 0, 0, /* ASCII
                                                                     characters
                                                                     from 0 to
                                                                     31 */
                  0x00000000,                                     /* SPACE */
                  0,          0,          0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0,          0x000000F0, 0, 0, /* ASCII characters from 33 to
                                                   47 */
                  0x0FFFFF0F,                   /* 0 */
                  0x000FF000,                   /* 1 */
                  0x00FF0FFF,                   /* 2 */
                  0x000FFFFF,                   /* 3 */
                  0x0F0FF0F0,                   /* 4 */
                  0x0F00FFFF,                   /* 5 */
                  0x0FF0FFFF,                   /* 6 */
                  0x000FFF00,                   /* 7 */
                  0x0FFFFFFF,                   /* 8 */
                  0x0F0FFFFF,                   /* 9 */
                  0,          0,          0, 0, 0, 0, 0, /* ASCII characters
                                                            from 58 to 64 */
                  0x0FFFFFF0,                            /* A */
                  0,                                     /* B */
                  0,                                     /* C */
                  0,                                     /* D */
                  0x0FF00FFF,                            /* E */
                  0x0FF00FF0,                            /* F */
                  0,                                     /* G */
                  0,                                     /* H */
                  0x0FF00000,                            /* I */
                  0,                                     /* J */
                  0,                                     /* K */
                  0,                                     /* L */
                  0x0FFFFF00,                            /* M */
                  0x00F0F0F0,                            /* N */
                  0,                                     /* O */
                  0,                                     /* P */
                  0,                                     /* Q */
                  0,                                     /* R */
                  0x0F00FFFF,                            /* S */
                  0x0FF000F0,                            /* T */
                  0,                                     /* U */
                  0,                                     /* V */
                  0,                                     /* W */
                  0,                                     /* X */
                  0,                                     /* Y */
                  0,                                     /* Z */
                  0,          0,          0, 0, 0, 0, /* ASCII characters from
                                                         91 to 96 */
                  0x0FFFFFF0,                         /* a */
                  0,                                  /* b */
                  0,                                  /* c */
                  0,                                  /* d */
                  0,                                  /* e */
                  0x0FF00FF0,                         /* f */
                  0,                                  /* g */
                  0,                                  /* h */
                  0x00F00000,                         /* i */
                  0,                                  /* j */
                  0,                                  /* k */
                  0,                                  /* l */
                  0x0FFFFF00,                         /* m */
                  0x00F0F0F0,                         /* n */
                  0x00F0F0FF,                         /* o */
                  0,                                  /* p */
                  0,                                  /* q */
                  0x00F000F0,                         /* r */
                  0x0F00FFFF,                         /* s */
                  0x0FF000F0,                         /* t */
                  0,                                  /* u */
                  0,                                  /* v */
                  0,                                  /* w */
                  0,                                  /* x */
                  0,                                  /* y */
                  0,                                  /* z */
                  0,          0,          0, 0, 0 /* ASCII characters from 123
                                                     to 127 */
              };

  string display_text;

  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

  bool draw_figure(const Cairo::RefPtr<Cairo::Context> &cr, int x, int y,
                   int segs);
  bool draw_negative(const Cairo::RefPtr<Cairo::Context> &cr);
  bool draw_display(const Cairo::RefPtr<Cairo::Context> &cr);
  bool switch_alarm(unsigned char alarm, bool state);
};

#endif
