#include <Arduino.h>
#include <unity.h>
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

void setUp()
{
    view->initializeGameScreen();
    gameController->reset();
    gameController->resetTimer();
}

void tearDown()
{
    view->getDiodes().turnOffAll();
}

void pickDiodeAndWaitForButton()
{
    int pickedDiode = gameController->pickRandomDiode();
    view->getDiodes().turnOnExclusively(pickedDiode);
    while (!gameController->isCorrectButtonPressed())
        delay(50); //To avoid busy waiting.
}

void shouldPick10RandomDiodesAndWaitForButtonPresses()
{
    for (size_t i = 0; i < 10; i++)
        pickDiodeAndWaitForButton();
}

void shouldDetectTimeExpiration()
{
    delay(2000 / 2);
    TEST_ASSERT_FALSE(gameController->hasTimeExpired());
    delay(2000);
    TEST_ASSERT_TRUE(gameController->hasTimeExpired());
}

void shouldCountMistakes()
{
    delay(2000 * 2);
    TEST_ASSERT_TRUE(gameController->hasTimeExpired());
    TEST_ASSERT_EQUAL(1, gameController->incrementMistakes());
    delay(2000 * 2);
    TEST_ASSERT_TRUE(gameController->hasTimeExpired());
    TEST_ASSERT_EQUAL(2, gameController->incrementMistakes());
}

void shouldVisualyRepresentTimeAsBarGraph()
{
    while (!gameController->hasTimeExpired())
    {
        float timeLeftPercentage = 100.0f * gameController->getTimeForReactionMillis() / gameController->getTimeForReactionMillis();
        view->setTimeBar(timeLeftPercentage);
    }
}

void shouldVisualyRepresentMistakesAsXes()
{
    delay(2000);
    for (size_t i = 0; i < 2; i++)
    {
        int mistakes = gameController->incrementMistakes();
        view->addMistakeMark(mistakes);
        delay(2000);
    }
}

void shouldVisualyRepresentScore()
{
    for (size_t i = 0; i < 10; i++)
    {
        pickDiodeAndWaitForButton();
        int score = gameController->addScore();
        view->setScore(score);
        int multiplier = gameController->getMultiplier();
        view->setMultiplier(multiplier);
    }
}

void setup()
{
    delay(2000);
    view = new View(lcd, diodes, buzzer);
    gameController = new GameController(buttons);
    UNITY_BEGIN();
    RUN_TEST(shouldPick10RandomDiodesAndWaitForButtonPresses);
    RUN_TEST(shouldDetectTimeExpiration);
    RUN_TEST(shouldCountMistakes);
    RUN_TEST(shouldVisualyRepresentTimeAsBarGraph);
    RUN_TEST(shouldVisualyRepresentMistakesAsXes);
    RUN_TEST(shouldVisualyRepresentScore);
    UNITY_END();
    delete view;
    delete gameController;
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}