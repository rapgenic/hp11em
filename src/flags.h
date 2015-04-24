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
    void setBase(base_t baseval);
    base_t getBase() const;

private:
    bool stackDisabled = false;
    base_t base = B_OCT;
    /*    bool numberWriting = false;
        bool numberDecimal = false;
        int numberDecCount = 0;
        DWriteMode_t displayWMode = M_DGT;*/
};

#endif // FLAGS_H
