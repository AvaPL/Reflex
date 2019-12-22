#include "Buzzer.h"

Buzzer::Buzzer(byte pin) : pin(pin)
{
}

void Buzzer::playTone(unsigned int frequency, unsigned long durationMillis)
{
    tone(pin, frequency, durationMillis);
}