#include "GameController.h"

GameController::GameController(Buttons &buttons) : buttons(buttons)
{
    randomSeed(analogRead(A1));
    timeForReactionMillis = START_TIME_FOR_REACTION_MILLIS;
    mode = MODE::SLOW;
    score = 0;
    multiplier = 1;
    streak = 0;
    mistakes = 0;
}

int GameController::pickRandomDiode()
{
    pickedDiode = random(0, Diodes::DIODES_COUNT);
    return pickedDiode;
}

bool GameController::isCorrectButtonPressed()
{
    return buttons.getOn() == pickedDiode;
}

bool GameController::isCorrectButtonPressed(unsigned long debounceTimeMillis)
{
    if (buttons.getOn() < 0)
        return false;
    delay(debounceTimeMillis);
    return buttons.getOn() == pickedDiode;
}

unsigned long GameController::getRemainingTimeForReactionMillis()
{
    int elapsedTimeMillis = millis() - lastTimestepMillis;
    return timeForReactionMillis - elapsedTimeMillis;
}

bool GameController::hasTimeExpired()
{
    return millis() - lastTimestepMillis > timeForReactionMillis;
}

void GameController::resetTimer()
{
    lastTimestepMillis = millis();
}

long GameController::addScore()
{
    score += multiplier;
    ++streak;
    updateMultiplier();
    updateTimeForReaction();
    return score;
}

void GameController::updateMultiplier()
{
    if (multiplier < 9 && streak == multiplier)
    {
        ++multiplier;
        streak = 0;
    }
}

void GameController::updateTimeForReaction()
{
    float timeMultiplier = mode == MODE::SLOW ? SLOW_TIME_MULTIPLIER : FAST_TIME_MULTIPLIER;
    timeForReactionMillis = (unsigned long)(timeMultiplier * timeForReactionMillis);
}

int GameController::incrementMistakes()
{
    streak = 0;
    multiplier = 1;
    return ++mistakes;
}

void GameController::reset()
{
    timeForReactionMillis = START_TIME_FOR_REACTION_MILLIS;
    mode = MODE::SLOW;
    score = 0;
    multiplier = 1;
    streak = 0;
    mistakes = 0;
}

unsigned long GameController::getTimeForReactionMillis()
{
    return timeForReactionMillis;
}

int GameController::getMultiplier()
{
    return multiplier;
}

GameController::MODE GameController::getMode()
{
    return mode;
}

void GameController::setMode(MODE mode)
{
    this->mode = mode;
}