#pragma once

#include <LiquidCrystal_I2C.h>
#include "Diodes.h"
#include "Buzzer.h"
#include "LCDBarGraph.h"

class View
{

private:
    LiquidCrystal_I2C &lcd;
    Diodes &diodes;
    Buzzer &buzzer;
    LCDBarGraph lcdBarGraph;

public:
    /**
     * @param lcd - LCD that is already initialized. 
     */
    View(LiquidCrystal_I2C &lcd, Diodes &diodes, Buzzer &buzzer);
    void printWelcomeScreen();
    void printCountdown();
    void initializeGameScreen();
    void setScore(long score);
    void setMultiplier(int multiplier);
    void addMistakeMark(int mistakeNumber);
    void setTimeBar(float percentageFill);
    void printScore(long score, long highscore);
    void printNewHighscore(long newHighscore);
    LiquidCrystal_I2C &getLcd();
    Diodes &getDiodes();
    Buzzer &getBuzzer();

private:
    void printAnimatedLines(String topLine, String bottomLine);
    void printCountdownNumber(int number, byte column, byte row);
};
