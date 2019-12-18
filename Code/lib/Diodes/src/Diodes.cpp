#include "Diodes.h"

Diodes::Diodes(byte latchPin, byte dataPin, byte clockPin)
    : latchPin(latchPin), dataPin(dataPin), clockPin(clockPin)
{
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    updateOutput();
}

void Diodes::turnOnExclusively(int diodeNumber)
{
    outputValues[0] = 0x00;
    outputValues[1] = 0x00;
    outputValues[diodeNumber / 8] = 1 << (diodeNumber % 8);
    updateOutput();
}

void Diodes::turnOffAll()
{
    outputValues[0] = 0x00;
    outputValues[1] = 0x00;
    updateOutput();
}

void Diodes::updateOutput()
{
    shiftOut(dataPin, clockPin, MSBFIRST, outputValues[1]);
    shiftOut(dataPin, clockPin, MSBFIRST, outputValues[0]);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
}