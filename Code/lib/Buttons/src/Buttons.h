#pragma once

#include <Arduino.h>
#include "Range.h"

class Buttons
{
private:
    const static int buttonsCount = 16;
    const static Range inactive;
    const static Range buttonRanges[buttonsCount];

    byte pin;

public:
    Buttons(byte pin) : pin(pin) {}
    bool isAnyOn() const;
    bool isOn(byte buttonNumber) const;
    static int getButtonsCount();
};
