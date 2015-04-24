/*
 * displaymodule.h
 *
 *  Created on: 26/giu/2014
 *      Author: giulio
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

#include <cln/cln.h>
using namespace cln;

#include "signals.h"
#include "flags.h"

class DisplayModule : public sigc::trackable {
public:
    DisplayModule(Signals *hpsignals_r, Flags *hpflags_r);

    bool printStringDisplay(string disp);
    bool printNumberDisplay(cl_R numb);

    string to_display(double num);
private:
    Signals *hpSignals;
    Flags *hpFlags;
};

#endif /* DISPLAYMODULE_H_ */
