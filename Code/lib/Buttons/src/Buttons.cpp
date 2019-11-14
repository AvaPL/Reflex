#include "Buttons.h"

//TODO: Add valid buttons ranges.
const Range Buttons::buttonsRanges[Buttons::BUTTONS_COUNT]{Range(20, 60),
                                                           Range(61, 100),
                                                           Range(101, 140),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0),
                                                           Range(0, 0)};

int Buttons::getOn() const
{
    int voltage = analogRead(pin);
    for (size_t i = 0; i < BUTTONS_COUNT; i++)
        if (buttonsRanges[i].containsValue(voltage))
            return i;
    return -1;
}