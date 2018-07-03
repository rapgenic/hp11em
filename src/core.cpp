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

#include "core.h"

Core::Core(Signals *hpSignals_r) {
  // Initializing variables
  hpSignals = hpSignals_r;
  hpSignals->signal_input().connect(sigc::mem_fun(*this, &Core::input));
  hpSignals->signal_gui_ready().connect(sigc::mem_fun(*this, &Core::gui_init));

  status = S_IDLE;
  error = E_NONE;
  fkeys = F_NONE;
  mkeys = M_NONE;
  key = -1;

  stack_nolift_required = false;

  reset_input_mode();

  notation = N_FIX;
  precision = 4;
  trigonometric_mode = T_DEG;

  waiting_data_len = 0;
}

void Core::gui_init() {
  display();
#ifdef DEBUG
  hpSignals->sig_update_register_table_emit(hpAMS.get_x(), hpAMS.get_y(),
                                            hpAMS.get_z(), hpAMS.get_t(),
                                            hpAMS.get_lst_x());
#endif
}

Core::~Core() {}

void Core::reset_input_mode() {
  decimal = false;
  exp = false;
  decimal_figures_number = 1;
  figures_number = 0;
  start_zero_figures_number = 0;
  exp_val = 0;
}

void Core::reset_waitdata_mode() {
  waitingdata_cb = keys_cb[key][fkeys];
  waiting_data_len = 0;
  previous_status = status;
}

void Core::ignore_waitdata() {
  status = previous_status;
  f_key_set(waiting_data[waiting_data_len - 1].fg);
  input(waiting_data[waiting_data_len - 1].key);
}

void Core::input(int _key) {
  key = _key;

#ifdef DEBUG
  cerr << KYEL << "CORE: received input: " << key << endl;
#endif

  switch (key) {
  case K_SDF:
  case K_GDF:
    mkeys = M_NONE;
    f_key_toggle(key);
    break;
  case K_ONF:
    shutdown();
    break;
  case K_REL:
    switch (status) {
    case S_PREFIX:
      /*
       * Resetting INPUT variables
       */
      reset_input_mode();
      status = S_IDLE;
      f_key_set(F_NONE);
      display();
      break;
    }
#ifdef DEBUG
    cerr << KBLU << "CORE SIGNAL - Key released" << KRST << endl;
#endif
    break;
  default:
    switch (status) {
    case S_IDLE:
      (this->*keys_cb[key][fkeys])();

      if (status != S_ERR)
        switch (key_status[key][fkeys]) {
        case S_INPUT:
          status = S_INPUT;
          break;
        case S_WAITDATA:
          reset_waitdata_mode();

          status = S_WAITDATA;
          break;
        case S_PREFIX:
          status = S_PREFIX;
          break;
        }

      if (!(key == K_GTO && fkeys != F_NONE))
        mkeys = M_NONE;
      f_key_set(F_NONE);

      display();

      break;
    case S_INPUT:
      (this->*keys_cb[key][fkeys])();

      if (status != S_ERR)
        switch (key_status[key][fkeys]) {
        case S_IDLE:
          /*
           * Resetting INPUT variables
           */
          reset_input_mode();

          status = S_IDLE;

          break;
        case S_WAITDATA:
          reset_waitdata_mode();

          status = S_WAITDATA;
          break;
        case S_PREFIX:
          status = S_PREFIX;
          break;
        }

      if (!(key == K_GTO && fkeys != F_NONE))
        mkeys = M_NONE;
      f_key_set(F_NONE);

      display();

      break;
    case S_WAITDATA:
      waiting_data[waiting_data_len].key = key;
      waiting_data[waiting_data_len].fg = fkeys;
      waiting_data_len++;

      (this->*waitingdata_cb)();

      display();

      break;
    case S_PREFIX:
      display();
      break;
    case S_ERR:
      error = E_NONE;
      status = S_IDLE;

      display();

      break;
    default:
      break;
    }
#ifdef DEBUG
    hpSignals->sig_update_register_table_emit(hpAMS.get_x(), hpAMS.get_y(),
                                              hpAMS.get_z(), hpAMS.get_t(),
                                              hpAMS.get_lst_x());
    cerr << KBLU << "Pressed Key Number: " << key << KRST << endl;
#endif
    break;
  }
}

void Core::f_key_set(unsigned char value) {
  if (value == F_NONE) {
    fkeys = F_NONE;
    hpSignals->sig_alarm_emit(A_GDF, false);
    hpSignals->sig_alarm_emit(A_SDF, false);
  } else if (value == F_FKEY) {
    fkeys = F_FKEY;
    hpSignals->sig_alarm_emit(A_GDF, false);
    hpSignals->sig_alarm_emit(A_SDF, true);
  } else if (value == F_GKEY) {
    fkeys = F_GKEY;
    hpSignals->sig_alarm_emit(A_GDF, true);
    hpSignals->sig_alarm_emit(A_SDF, false);
  }
}

void Core::f_key_toggle(int key) {
  if (key == K_SDF) {
    if (fkeys == F_FKEY)
      f_key_set(F_NONE);
    else if (fkeys == F_NONE || fkeys == F_GKEY)
      f_key_set(F_FKEY);
  } else if (key == K_GDF) {
    if (fkeys == F_GKEY)
      f_key_set(F_NONE);
    else if (fkeys == F_NONE || fkeys == F_FKEY)
      f_key_set(F_GKEY);
  }
}

void Core::display() {
  double numb = hpAMS.get_x();
  double pnumb = fabs(numb);
  int log10_pnumb = (int)floor(log10(pnumb));

  char display_text[22] = "";

  memset(display_text, ' ', 22);

  char *display_text_ptr = display_text;

  if (numb >= 0)
    *display_text_ptr++ = '+';
  else
    *display_text_ptr++ = '-';

  switch (status) {
  case S_IDLE:
    if (numb == BIGGEST_REPR) {
      double_to_display(pnumb, 9, display_text_ptr, N_SCI);
    } else if (numb == SMALLST_REPR) {
      double_to_display(pnumb, 9, display_text_ptr, N_SCI);
    } else if (notation == N_FIX &&
               (log10_pnumb < 10 && log10_pnumb >= -precision || numb == 0)) {
      double_to_display(pnumb, precision, display_text_ptr, N_FIX);
    } else if (notation == N_SCI ||
               (notation == N_FIX &&
                (log10_pnumb >= 10 || log10_pnumb < -precision))) {
      double_to_display(pnumb, precision, display_text_ptr, N_SCI);
    } else if (notation == N_ENG) {
      double_to_display(pnumb, precision, display_text_ptr, N_ENG);
    } else {
      std::cerr << KRED << "Bug: Value " << numb
                << " can't be displayed!!! Please send this line to a developer"
                << KRST << std::endl
                << std::flush;
    }

    hpSignals->sig_display_emit(display_text);
    draw_trig_announciator();
    break;
  case S_INPUT:
    if (exp) {
      pnumb /= pow(10, exp_val);
    }

    if (start_zero_figures_number) {
      memset(display_text_ptr, '0', start_zero_figures_number);
      display_text_ptr += start_zero_figures_number - 1;
    }

    double_to_display(pnumb, decimal_figures_number - 1, display_text_ptr,
                      N_FIX, decimal);

    if (exp) {
      int n, i;
      int expv = 0;

      expv = exp_val;

      display_text_ptr = display_text;

      display_text_ptr += decimal ? 9 : 8;

      if (expv < 0) {
        *display_text_ptr++ = '-';
        expv = -expv;
      } else {
        *display_text_ptr++ = ' ';
      }
      n = 0;
      display_text_ptr += 10;
      do {
        n++;
        *display_text_ptr++ = (expv % 10) + '0';
        expv /= 10;
      } while (expv || n < 2);
      for (i = n; n > 0; n--)
        *(display_text_ptr - 11 - i + n) = *(display_text_ptr - n);
      display_text_ptr -= 10;
    }

    hpSignals->sig_display_emit(display_text);
    draw_trig_announciator();
    break;
  case S_PREFIX:
    if (pnumb != 0) {
      while ((int)floor(log10(pnumb)) < 9) {
        pnumb *= 10.0;
      }

      double_to_display(pnumb, 0, display_text_ptr, N_FIX, false);
    } else {
      sprintf(display_text_ptr, "0000000000");
    }
    cerr << display_text << endl;
    hpSignals->sig_display_emit(display_text);
    break;
  case S_ERR:
    sprintf(display_text, "+Error %d", error);
    hpSignals->sig_display_emit(display_text);
    cerr << KRED << "CALCULATOR ERROR " << error << KRST << endl;
    break;
  default:
    break;
  }
}

void Core::draw_trig_announciator() {
  switch (trigonometric_mode) {
  case T_RAD:
    hpSignals->sig_alarm_emit(A_GRD, false);
    hpSignals->sig_alarm_emit(A_RAD, true);
    break;
  case T_GRD:
    hpSignals->sig_alarm_emit(A_GRD, true);
    hpSignals->sig_alarm_emit(A_RAD, false);
    break;
  case T_DEG:
    hpSignals->sig_alarm_emit(A_GRD, false);
    hpSignals->sig_alarm_emit(A_RAD, false);
  }
}

void Core::double_to_display(double value, short _precision, char *_buf,
                             notation_t _notation, char dot) {
  char *tb, *buf_pointer;
  short t1, t2, dec_point_pos;
  int exp10;

  buf_pointer = _buf;
  exp10 = 0;

  if (value != 0)
    exp10 = floor(log10(value));

  value /= pow(10, exp10);

  switch (_notation) {
  case N_ENG:
  case N_SCI:
    dec_point_pos = 0;
    break;
  case N_FIX:
    if (exp10 < 0) {
      t1 = _precision;

      *buf_pointer++ = '0';
      if ((t1 = _precision) || dot)
        *buf_pointer++ = '.';

      t2 = 0;

      while (--t2 > exp10 && _precision) {
        *buf_pointer++ = '0';
        _precision--;
      }

      if (exp10 < (-t1 - 1)) {
        return;
      }

      dec_point_pos = 1;
    } else {
      dec_point_pos = -exp10;
    }
    break;
  }

  t2 = dec_point_pos;

  while (t2 <= _precision) {
    value -= t1 = value;
    value *= 10;

    *buf_pointer++ = t1 + '0';
    if (!t2++ && (_precision || dot)) {
      *buf_pointer++ = '.';
    }
  }

  if (value >= 5) {
    t1 = 1;
    tb = buf_pointer - 1;
    do {
      if (*tb != '.') {
        if ((*tb += t1) == ('9' + 1)) {
          *tb = '0';
          t1 = 1;
        } else {
          t1 = 0;
        }
      }
    } while (tb-- > _buf);
    if (t1) {
      switch (_notation) {
      case N_ENG:
      case N_SCI:
        tb = buf_pointer;
        while (tb > _buf) {
          if (*(tb - 1) == '.') {
            *tb = *(tb - 2);
            tb--;
          } else {
            *tb = *(tb - 1);
          }
          tb--;
        }
        exp10++;
        break;
      case N_FIX:
        tb = ++buf_pointer;
        while (tb > _buf) {
          *tb = *(tb - 1);
          tb--;
        }
        break;
      }
      *_buf = '1';
    }
  }

  switch (_notation) {
  case N_ENG:
  case N_SCI:
    buf_pointer = _buf;

    buf_pointer += 8;

    if (exp10 < 0) {
      *buf_pointer++ = '-';
      exp10 = -exp10;
    } else {
      *buf_pointer++ = ' ';
    }
    t1 = 0;
    buf_pointer += 10;
    do {
      t1++;
      *buf_pointer++ = (exp10 % 10) + '0';
      exp10 /= 10;
    } while (exp10 || t1 < 2);
    for (t2 = t1; t1 > 0; t1--)
      *(buf_pointer - 11 - t2 + t1) = *(buf_pointer - t1);
    buf_pointer -= 10;
    break;
  case N_FIX:
    break;
  }

  *buf_pointer = '\0';
}

void Core::shutdown() { hpSignals->sig_off_emit(); }
