#pragma once

#include <Arduino.h>

class Diodes
{

public:
    const static int DIODES_COUNT = 16;

private:
    byte latchPin;
    byte dataPin;
    byte clockPin;
    byte outputValues[2] = {0x00, 0x00};

public:
    Diodes(byte latchPin, byte dataPin, byte clockPin);
    void turnOnExclusively(int diodeNumber);
    void turnOffAll();

private:
    void updateOutput();
};
