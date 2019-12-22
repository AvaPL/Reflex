#include <Arduino.h>
#include "View.h"
#include "GameController.h"

const byte LCD_ADDRESS = 0x20;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

const byte LATCH_PIN = 4;
const byte DATA_PIN = 6;
const byte CLOCK_PIN = 5;

Diodes diodes(LATCH_PIN, DATA_PIN, CLOCK_PIN);

const byte BUZZER_PIN = 8;

Buzzer buzzer(BUZZER_PIN);

View *view; //Pointer, because of global variables initialization order.

const byte BUTTONS_PIN = A0;

Buttons buttons(BUTTONS_PIN);

GameController *gameController; //Pointer, because of global variables initialization order.

void setup()
{
  lcd.init();
  view = new View(lcd, diodes, buzzer);
  gameController = new GameController(buttons);
  view->getDiodes().turnOffAll();
  view->printWelcomeScreen();
  delay(2000);
}

//TODO: Add time for reaction decrease.
//TODO: Add slow/fast modes.
//TODO: Add highscores.
//TODO: Add buzzer sounds.
//TODO: Cleanup code (all classes including tests).

void startNewGame();
void pickDiode();
void doGameStep();
void addMistake();
void addScore();
void updateTimer();
void endGame();

int score = 0;
int mistakes = 0;
int pickedDiode;

void loop()
{
  startNewGame();
  while (mistakes < 3)
    doGameStep();
  endGame();
  delay(5000);
}

void startNewGame()
{
  view->printCountdown();
  view->initializeGameScreen();
  gameController->reset();
  gameController->resetTimer();
  pickDiode();
}

void pickDiode()
{
  pickedDiode = gameController->pickRandomDiode();
  view->getDiodes().turnOnExclusively(pickedDiode);
}

void doGameStep()
{
  if (gameController->hasTimeExpired())
    addMistake();
  else if (gameController->isCorrectButtonPressed(5))
    addScore();
  updateTimer();
}

void addMistake()
{
  mistakes = gameController->incrementMistakes();
  view->addMistakeMark(mistakes);
  view->setMultiplier(gameController->getMultiplier());
  pickDiode();
  gameController->resetTimer();
}

void addScore()
{
  score = gameController->addScore();
  view->setScore(score);
  view->setMultiplier(gameController->getMultiplier());
  pickDiode();
  gameController->resetTimer();
}

void updateTimer()
{
  float timeLeftPercentage = 100.0f * gameController->getRemainingTimeForReactionMillis() / gameController->getTimeForReactionMillis();
  view->setTimeBar(timeLeftPercentage);
}

void endGame()
{
  view->getDiodes().turnOffAll();
  view->printScore(score, 0);
  score = 0;
  mistakes = 0;
}