#pragma once

#include <Arduino.h>

class Buzzer
{

private:
    byte pin;

public:
    const static unsigned int TONE_LOW = 1000;
    const static unsigned int TONE_MEDIUM = 2000;
    const static unsigned int TONE_HIGH = 3000;

public:
    Buzzer(byte pin) : pin(pin) {}
    void playTone(unsigned int frequency, unsigned long duration);
};
