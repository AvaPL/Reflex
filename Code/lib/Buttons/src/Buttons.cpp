#include "Buttons.h"

const Range Buttons::inactive = Range(700, 1023);
//TODO: Add valid button ranges.
const Range Buttons::buttonRanges[Buttons::buttonsCount]{Range(20, 60),
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

bool Buttons::isAnyOn() const
{
    int voltage = analogRead(pin);
    for (auto &&range : buttonRanges)
        if (range.containsValue(voltage))
            return true;
    return false;
}

bool Buttons::isOn(byte buttonNumber) const
{
    int voltage = analogRead(pin);
    return buttonRanges[buttonNumber].containsValue(voltage);
}

int Buttons::getButtonsCount()
{
    return buttonsCount;
}