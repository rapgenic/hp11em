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

#ifndef DISPLAYMODULE_H_
#define DISPLAYMODULE_H_

#include "config.h"

#include <string>
using namespace std;

#include <iomanip>
using namespace std;

#include <sstream>
using namespace std;

#include <ostream>
using namespace std;

#include <cln/cln.h>
using namespace cln;

#include <locale>
using namespace std;

#include "signals.h"
#include "flags.h"

class DisplayModule : public sigc::trackable {
public:
    DisplayModule(Signals *hpsignals_r, Flags *hpflags_r);

    bool printStringDisplay(string disp);
    bool printNumberDisplay(cl_R numb);
    bool printErrorDisplay(int x);

    string to_display(double num);
private:
    Signals *hpSignals;
    Flags *hpFlags;
};

#endif /* DISPLAYMODULE_H_ */
