#include "Buttons.h"
#include <unity.h>

const byte BUTTON_PIN = A0;

Buttons buttons(BUTTON_PIN);

void setup()
{
    delay(2000);
    UNITY_BEGIN();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    UNITY_END();
}

void blink(int repeat)
{
    for (int i = 0; i < repeat; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}

void loop()
{
    if (!buttons.isAnyOn())
        return;
    delay(100); //TODO: Choose optimal delay.
    for (int i = 0; i < Buttons::getButtonsCount(); i++)
        if (buttons.isOn(i))
        {
            blink(i + 1);
            return;
        }
}