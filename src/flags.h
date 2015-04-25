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

#ifndef FLAGS_H
#define FLAGS_H

#include "config.h"

class Flags {
public:

    typedef enum {
        B_OCT = 8,
        B_DEC = 10,
        B_EXA = 16
    } base_t;

    typedef enum {
        S_ERR = 0,
        S_RUN,
        S_PRG
    } state_t;
    /*
        typedef enum {
            M_DGT,
            M_RES,
            M_PRG,
        } DWriteMode_t;*/

    /*    bool isNumberWriting() const;
        void setNumberWriting(bool number);
        bool isNumberDecimal() const;
        void setNumberDecimal(bool value);
        DWriteMode_t getDisplayWMode() const;
        void setDisplayWMode(DWriteMode_t mode);
        int getNumberDecCount() const;
        void incNumberDecCount();
        void resNumberDecimal();*/
    void setStackDisabled(bool value);
    bool isStackDisabled() const;
    void setPendingData(bool value);
    bool isPendingData() const;
    void setBase(base_t baseval);
    base_t getBase() const;
    void setState(state_t st);
    state_t getState() const;

private:
    bool stackDisabled = false;
    bool pendingData = false;
    base_t base = B_OCT;
    state_t state = S_RUN; 
    /*    bool numberWriting = false;
        bool numberDecimal = false;
        int numberDecCount = 0;
        DWriteMode_t displayWMode = M_DGT;*/
};

#endif // FLAGS_H
