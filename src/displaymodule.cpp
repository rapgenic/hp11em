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
using std::string;

#include <cstring>

#include <iostream>
using std::cerr;
using std::endl;

#include <iomanip>
using std::setprecision;
using std::fixed;

#include <sstream>
using std::ostringstream;

#include <locale>
using std::locale;

#include <cmath>
using std::fabs;

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

bool DisplayModule::printNumberDisplay(double numb) {
    char display_text[22] = "";
    
    // Assuring that numb doesn't get truncated
    numb += 5.0 * pow10(-10.0);

    // Working with positive numbers only
    double pnumb = fabs(numb);

    int exp = 0;
    int exppos = 0;
    long pnumbi = 0;
    double pnumbd = 0;
    char spnumbi[22] = "";
    char spnumbd[22] = "";
    char sexp[3] = "";

#ifdef DEBUG
    cerr << KCYN << endl;
#endif

    if (hpFlags->getNotation() == Flags::N_FIX && numb < pow10(10)) {
        pnumbi = (long) pnumb;
        pnumbd = pnumb - (double) pnumbi;

        longToString(pnumbi, spnumbi, 1);
        longToString((long) (pnumbd * pow(10, hpFlags->getNotPrecision())), spnumbd, hpFlags->getNotPrecision());

        sprintf(display_text, "%c%s,%s", numb >= 0 ? '+' : '-', spnumbi, spnumbd);
    } else if (hpFlags->getNotation() == Flags::N_SCI || (hpFlags->getNotation() == Flags::N_FIX && numb > pow10(10))) {
        //double tpnumb = pnumb;

        // calculates the exponent
        if (pnumb >= 10.0)
            while (pnumb >= 10.0) {
                pnumb /= 10.0;
                exp++;
            }
        else if (pnumb < 1.0) 
            while (pnumb < 1.0) {
                pnumb *= 10.0;
                exp--;
            }            

        pnumbi = (long) pnumb;
        pnumbd = pnumb - (double) pnumbi;

        longToString(pnumbi, spnumbi, 1);
        longToString((long) (pnumbd * pow10(hpFlags->getNotPrecision())), spnumbd, hpFlags->getNotPrecision());

        sprintf(display_text, "%c%s,%s", numb >= 0 ? '+' : '-', spnumbi, spnumbd);

        // Adding exponent to string
        longToString(abs(exp), sexp, 2);

        // calculate the position of the exponent in the display:
        // we need to do all these strange calculations because only
        // figures are considered while converting the string to 
        // display lines so for example a string like this
        //    "+1.1111"
        // is a 7 char string, but when printing to the display
        // only
        //    "11111"
        // are considered.
        // in conclusion '+' '-' '.' ',' aren't considered as a character

        exppos = strlen(display_text)+(10 - (strlen(spnumbi) + strlen(spnumbd)));

        for (int h = strlen(display_text); h < 22; h++)
            display_text[h] = ' ';

        // insert a space or a minus before the exponent to distinguish it from the rest of
        // the number
        display_text[exppos - 3] = exp >= 0 ? ' ' : '-';
        display_text[exppos - 2] = sexp[0];
        display_text[exppos - 1] = sexp[1];
        display_text[exppos] = '\0';
    }

#ifdef DEBUG
    cerr << "DISPLAY OUTPUT: " << display_text << KRST << endl;
#endif

    hpSignals->sig_display_emit(display_text);

    return true;
}

bool DisplayModule::longToString(long x, char str[], int d) {
    int i = 0;
    int z = 0;
    int j;
    int temp;
    
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    // reversing string
    j = i - 1;

    while (z < j) {
        temp = str[z];
        str[z] = str[j];
        str[j] = temp;
        z++;
        j--;
    }

    str[i] = '\0';

    return true;
}

bool DisplayModule::printErrorDisplay(int x) {
    char display_text[22];

    sprintf(display_text, "+Error %d", x);

    hpSignals->sig_display_emit(display_text);

    cerr << KRED << "CALCULATOR ERROR " << x << KRST << endl;

    return true;
}

string DisplayModule::to_display(double num) {
    return "Error ";
}