#pragma once

#include <Arduino.h>

class Buzzer
{

public:
    const static unsigned int TONE_LOW = 1000;
    const static unsigned int TONE_MEDIUM = 2000;
    const static unsigned int TONE_HIGH = 3000;

private:
    byte pin;

public:
    Buzzer(byte pin) : pin(pin) {}
    void playTone(unsigned int frequency, unsigned long durationMillis);
};
