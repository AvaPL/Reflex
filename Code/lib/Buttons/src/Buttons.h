#pragma once

#include <Arduino.h>
#include "Range.h"

class Buttons
{

public:
    const static int BUTTONS_COUNT = 16;

private:
    const static Range buttonsRanges[BUTTONS_COUNT];

    byte pin;

public:
    Buttons(byte pin);
    int getOn();
};
