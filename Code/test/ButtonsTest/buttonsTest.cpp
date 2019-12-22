#include <unity.h>
#include "Buttons.h"

const byte BUTTONS_PIN = A0;

Buttons buttons(BUTTONS_PIN);

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
    int onButton = buttons.getOn();
    if (onButton >= 0)
        blink(onButton + 1);
}