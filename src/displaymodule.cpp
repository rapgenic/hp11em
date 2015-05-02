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

#include "config.h"

#include <string>
using std::to_string;

#include <iostream>
using std::cerr;
using std::endl;

#include <iomanip>
using std::setprecision;
using std::fixed;

#include <sstream>
using std::ostringstream;

#include <cln/cln.h>
using cln::float_approx;

#include <locale>
using std::locale;

#include "signals.h"
#include "flags.h"
#include "colors.h"
#include "displaymodule.h"

DisplayModule::DisplayModule(Signals *hpsignals_r, Flags *hpflags_r) {
    hpSignals = hpsignals_r;
    hpFlags = hpflags_r;
}

bool DisplayModule::printStringDisplay(string disp) {
    hpSignals->sig_display_emit(disp);

    return true;
}

bool DisplayModule::printNumberDisplay(cl_R numb) {
    ostringstream display_stream;
    
    display_stream.imbue(locale("en_US.UTF-8"));
    display_stream << fixed;
    display_stream << setprecision(4) << float_approx(numb);
    
#ifdef DEBUG  
    cerr << KBLU << "printNumberDisplay(): number = " << display_stream.str() << KRST << endl;  
#endif
    
    hpSignals->sig_display_emit(((numb >= 0) ? " " : "") + display_stream.str());

    return true;
}

bool DisplayModule::printErrorDisplay(int x) {
    hpSignals->sig_display_emit("Error"+to_string(x));
    
    cerr << KRED << "CALCULATOR ERROR " << x << KRST << endl;
    
    return true;
}

string DisplayModule::to_display(double num) {
    return "Error ";
}
