#pragma once

#include <LiquidCrystal_I2C.h>
#include "LCDBarGraph.h"
#include "Diodes.h"
#include "Buzzer.h"

class View
{

private:
    LiquidCrystal_I2C &lcd;
    Diodes &diodes;
    Buzzer &buzzer;
    LCDBarGraph lcdBarGraph;

public:
    View(LiquidCrystal_I2C &lcd, Diodes &diodes, Buzzer &buzzer);
    void printWelcomeScreen();
    void printCountdown();
    void printScore(long score, long highscore);
    void printNewHighscore(long newHighscore);
    LiquidCrystal_I2C &getLcd();
    Diodes &getDiodes();
    Buzzer &getBuzzer();

private:
    void printAnimatedLines(String topLine, String bottomLine);
    void printCountdownNumber(int number, byte column, byte row);
};
