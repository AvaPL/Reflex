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

//TODO: Pick another diode after mistake.
//TODO: Add time for reaction decrease.
//TODO: Add slow/fast modes.
//TODO: Add highscores.
//TODO: Add buzzer sounds.
//TODO: Cleanup code.

void loop()
{
  view->printCountdown();
  view->initializeGameScreen();
  gameController->reset();
  gameController->resetTimer();
  int score = 0;
  int mistakes = 0;
  int pickedDiode = gameController->pickRandomDiode();
  view->getDiodes().turnOnExclusively(pickedDiode);
  while (mistakes < 3)
  {
    if (gameController->hasTimeExpired())
    {
      mistakes = gameController->incrementMistakes();
      view->addMistakeMark(mistakes);
      view->setMultiplier(gameController->getMultiplier());
      gameController->resetTimer();
    }
    else if (gameController->isCorrectButtonPressed())
    {
      score = gameController->addScore();
      view->setScore(score);
      view->setMultiplier(gameController->getMultiplier());
      pickedDiode = gameController->pickRandomDiode();
      view->getDiodes().turnOnExclusively(pickedDiode);
      gameController->resetTimer();
    }
    float timeLeftPercentage = 100.0f * (gameController->getTimeForReactionMillis() - gameController->getTimeElapsedMillis()) / gameController->getTimeForReactionMillis();
    view->setTimeBar(timeLeftPercentage);
  }
  view->getDiodes().turnOffAll();
  view->printScore(score, 0);
  delay(5000);
}