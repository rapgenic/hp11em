/*
 * displaymodule.cpp
 *
 *  Created on: 26/giu/2014
 *      Author: giulio
 */

#include "displaymodule.h"
#include "flags.h"

DisplayModule::DisplayModule(Signals *hpsignals_r, Flags *hpflags_r) {
    hpSignals = hpsignals_r;
    hpFlags = hpflags_r;
}

bool DisplayModule::printStringDisplay(string disp) {
    hpSignals->sig_display_emit(disp);

    return true;
}

bool DisplayModule::printNumberDisplay(cl_R numb) {
    //string disp = std::to_string(numb);

    //disp.insert(0, (numb >= 0 ? "+" : "-"));

    //hpsignals->sig_display_emit(disp);

    //hpsignals->sig_display_emit("+7357");

    ostringstream number;
   
    number << fixed;
    number << setprecision(4) << float_approx(numb);
    
    hpSignals->sig_display_emit((numb < 0) ? "-" : "+" + number.str());

    return true;
}

string DisplayModule::to_display(double num) {
    return "ciao";
}
