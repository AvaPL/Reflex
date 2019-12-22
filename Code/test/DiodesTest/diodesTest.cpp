#include <Arduino.h>
#include <unity.h>
#include "Diodes.h"

const byte LATCH_PIN = 4;
const byte DATA_PIN = 6;
const byte CLOCK_PIN = 5;

Diodes diodes(LATCH_PIN, DATA_PIN, CLOCK_PIN);

void tearDown()
{
    diodes.turnOffAll();
}

void shouldTurnOnDiode0()
{
    diodes.turnOnExclusively(0);
    delay(5000);
}

void shouldTurnOnDiode8()
{
    diodes.turnOnExclusively(8);
    delay(5000);
}

void shouldTurnOnDiodesInOrder()
{
    for (int i = 0; i < Diodes::DIODES_COUNT; i++)
    {
        diodes.turnOnExclusively(i);
        delay(250);
    }
}

void setup()
{
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(shouldTurnOnDiode0);
    RUN_TEST(shouldTurnOnDiode8);
    RUN_TEST(shouldTurnOnDiodesInOrder);
    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}