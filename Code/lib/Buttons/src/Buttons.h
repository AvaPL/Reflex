#pragma once

#include <Arduino.h>
#include "Range.h"

class Buttons
{

public:
    const static int BUTTONS_COUNT = 16;
    const static Range buttonsRanges[BUTTONS_COUNT];
    const static Range inactiveRange;

private:
    byte pin;

public:
    Buttons(byte pin) : pin(pin) {}
    bool isAnyOn() const;
    bool isOn(byte buttonNumber) const;
};
