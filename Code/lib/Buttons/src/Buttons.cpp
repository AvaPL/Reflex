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
const Range Buttons::inactiveRange = Range(700, 1023);

bool Buttons::isAnyOn() const
{
    int voltage = analogRead(pin);
    for (auto &&range : buttonsRanges)
        if (range.containsValue(voltage))
            return true;
    return false;
}

bool Buttons::isOn(byte buttonNumber) const
{
    int voltage = analogRead(pin);
    return buttonsRanges[buttonNumber].containsValue(voltage);
}