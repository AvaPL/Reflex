#include "Buzzer.h"

void Buzzer::playTone(unsigned int frequency, unsigned long duration)
{
    tone(pin, frequency, duration);
}
