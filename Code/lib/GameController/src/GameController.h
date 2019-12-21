#pragma once

#include <Arduino.h>
#include "Diodes.h"
#include "Buttons.h"

class GameController
{

public:
    const static unsigned long startTimeForReactionMillis = 2000;

private:
    Buttons &buttons;
    unsigned long timeForReactionMillis;
    unsigned long lastTimestepMillis;
    int pickedDiode;
    long score;
    int multiplier;
    int streak;
    int mistakes;

public:
    GameController(Buttons &buttons);
    int pickRandomDiode();
    bool isCorrectButtonPressed();
    bool isCorrectButtonPressed(unsigned long debounceTimeMillis);
    unsigned long getTimeElapsedMillis();
    bool hasTimeExpired();
    void resetTimer();
    long addScore();
    int incrementMistakes();
    void reset();
    unsigned long getTimeForReactionMillis();
    int getMultiplier();
};