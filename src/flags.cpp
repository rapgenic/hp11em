#include "flags.h"

/*bool Flags::isNumberWriting() const {
    return numberWriting;
}

void Flags::setNumberWriting(bool writingNumber) {
    numberWriting = writingNumber;
}

bool Flags::isNumberDecimal() const {
    return numberDecimal;
}

void Flags::setNumberDecimal(bool decimal) {
    numberDecimal = decimal;
}

Flags::DWriteMode_t Flags::getDisplayWMode() const {
    return displayWMode;
}

void Flags::setDisplayWMode(DWriteMode_t dispmode) {
    displayWMode = dispmode;
}

int Flags::getNumberDecCount() const {
    return numberDecCount;
}

void Flags::incNumberDecCount() {
    numberDecCount++;
}

void Flags::resNumberDecimal() {
    numberDecimal = false;
    numberDecCount = 0;
}*/

void Flags::setStackDisabled(bool value) {
    stackDisabled = value;
}

bool Flags::isStackDisabled() const {
    return stackDisabled;
}

void Flags::setBase(base_t baseval) {
    base = baseval;
}

Flags::base_t Flags::getBase() const {
    return base;
}