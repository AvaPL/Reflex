#pragma once

#include <LiquidCrystal_I2C.h>
#include "Buzzer.h"
#include "Diodes.h"

class View
{

private:
    LiquidCrystal_I2C &lcd;
    Diodes &diodes;
    Buzzer &buzzer;

public:
    View(LiquidCrystal_I2C &lcd, Diodes &diodes, Buzzer &buzzer);
    void printWelcomeScreen();
    void printCountdown();
    LiquidCrystal_I2C &getLcd();
    Diodes &getDiodes();
    Buzzer &getBuzzer();

private:
    void printAnimatedLines(String topLine, String bottomLine);
    void printCountdownNumber(int number, byte column, byte row);
};
