#include "Buttons.h"

//TODO: Add valid buttons ranges.
const Range Buttons::buttonsRanges[Buttons::BUTTONS_COUNT]{Range(20, 60),
                                                           Range(61, 100),
                                                           Range(101, 140),
                                                           Range(141, 185),
                                                           Range(186, 225),
                                                           Range(226, 265),
                                                           Range(266, 305),
                                                           Range(306, 345),
                                                           Range(346, 390),
                                                           Range(391, 430),
                                                           Range(431, 470),
                                                           Range(471, 510),
                                                           Range(511, 550),
                                                           Range(551, 590),
                                                           Range(591, 635),
                                                           Range(636, 675)};

int Buttons::getOn() const
{
    int voltage = analogRead(pin);
    for (size_t i = 0; i < BUTTONS_COUNT; i++)
        if (buttonsRanges[i].containsValue(voltage))
            return i;
    return -1;
}