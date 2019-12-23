#include <Arduino.h>
#include <EEPROM.h>
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

const byte MODE_PIN = 7;

const int HIGHSCORE_ADDRESS_SLOW = 0;
const int HIGHSCORE_ADDRESS_FAST = HIGHSCORE_ADDRESS_SLOW + sizeof(long);

long highscoreSlow = 0;
long highscoreFast = 0;

void loadHighscores();
void initializeView();

void setup()
{
  lcd.init();
  pinMode(MODE_PIN, INPUT_PULLUP);
  gameController = new GameController(buttons);
  loadHighscores();
  initializeView();
}

void loadHighscores()
{
  EEPROM.get(HIGHSCORE_ADDRESS_SLOW, highscoreSlow);
  EEPROM.get(HIGHSCORE_ADDRESS_FAST, highscoreFast);
}

void initializeView()
{
  view = new View(lcd, diodes, buzzer);
  view->getDiodes().turnOffAll();
  view->printWelcomeScreen();
  delay(2000);
}

void startNewGame();
void setGameMode();
void pickDiode();
void doGameStep();
void addMistake();
void addScore();
void updateTimer();
void endGame();
void printScore();
void printHighscoreAndPlaySound();
void printScoreAndPlaySound(long highscore);
void updateHighscores();

long score = 0;
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
  setGameMode();
  gameController->resetTimer();
  pickDiode();
}

void setGameMode()
{
  int pinState = digitalRead(MODE_PIN);
  GameController::MODE mode = pinState == 0 ? GameController::MODE::SLOW : GameController::MODE::FAST;
  gameController->setMode(mode);
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
  view->getBuzzer().playTone(Buzzer::TONE_LOW, 200);
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
  printScore();
  updateHighscores();
  score = 0;
  mistakes = 0;
}

void printScore()
{
  long highscore = gameController->getMode() == GameController::MODE::SLOW ? highscoreSlow : highscoreFast;
  if (score > highscore)
    printHighscoreAndPlaySound();
  else
    printScoreAndPlaySound(highscore);
}

void printHighscoreAndPlaySound()
{
  view->printNewHighscore(score);
  Buzzer &buzzer = view->getBuzzer();
  buzzer.playTone(Buzzer::TONE_MEDIUM, 300);
  for (size_t i = 0; i < 3; i++)
  {
    buzzer.playTone(Buzzer::TONE_HIGH, 200);
    delay(100);
    buzzer.playTone(Buzzer::TONE_MEDIUM, 300);
    delay(100);
  }
}

void printScoreAndPlaySound(long highscore)
{
  view->printScore(score, highscore);
  Buzzer &buzzer = view->getBuzzer();
  for (size_t i = 0; i < 3; i++)
  {
    buzzer.playTone(Buzzer::TONE_MEDIUM, 100);
    delay(150);
  }
  buzzer.playTone(Buzzer::TONE_LOW, 300);
}

void updateHighscores()
{
  if (gameController->getMode() == GameController::MODE::SLOW)
  {
    highscoreSlow = max(score, highscoreSlow);
    EEPROM.put(HIGHSCORE_ADDRESS_SLOW, highscoreSlow);
  }
  else
  {
    highscoreFast = max(score, highscoreFast);
    EEPROM.put(HIGHSCORE_ADDRESS_FAST, highscoreFast);
  }
}