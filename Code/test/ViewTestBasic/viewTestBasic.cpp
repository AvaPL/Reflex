#include "View.h"
#include <Arduino.h>
#include <unity.h>

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

void tearDown()
{
    delay(2000);
    view->getLcd().clear();
    view->getDiodes().turnOffAll();
}

void shouldInitializeCorrectly()
{
    //Should start with empty lcd, diodes off and buzzer off.
}

void shouldPrintWelcomeScreen()
{
    view->printWelcomeScreen();
}

void shouldMakeBuzzerSound()
{
    view->getBuzzer().playTone(Buzzer::TONE_MEDIUM, 500);
}

void shouldTurnOnLed0Then5Then10Then15()
{
    Diodes &diodes = view->getDiodes();
    for (int i = 0; i <= 15; i += 5)
    {
        diodes.turnOnExclusively(i);
        delay(500);
    }
}

void shouldPrintCountdown()
{
    view->printCountdown();
}

void shouldPrintScoreWithHighscore()
{
    view->printScore(99, 999);
}

void shouldPrintNewHighscoreCentered()
{
    view->printNewHighscore(99);
    delay(2000);
    view->printNewHighscore(999);
}

void setup()
{
    delay(2000);
    view = new View(lcd, diodes, buzzer);
    UNITY_BEGIN();
    RUN_TEST(shouldInitializeCorrectly);
    RUN_TEST(shouldPrintWelcomeScreen);
    RUN_TEST(shouldMakeBuzzerSound);
    RUN_TEST(shouldTurnOnLed0Then5Then10Then15);
    RUN_TEST(shouldPrintCountdown);
    RUN_TEST(shouldPrintScoreWithHighscore);
    RUN_TEST(shouldPrintNewHighscoreCentered);
    UNITY_END();
    delete view;
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}