#include "Buzzer.h"

void Buzzer::playTone(unsigned int frequency, unsigned long durationMillis)
{
    tone(pin, frequency, durationMillis);
}
