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

void setUp()
{
    view->initializeGameScreen();
}

void tearDown()
{
    delay(2000);
}

void shouldInitializeGameScreen()
{
}

void shouldSetScoreTo1000()
{
    view->setScore(1000);
}

void shouldSetMultiplierTo5()
{
    view->setMultiplier(5);
}

void shouldAddMistakeMark1Then2()
{
    view->addMistakeMark(1);
    delay(2000);
    view->addMistakeMark(2);
}

void shouldSetTimeBarTo60Percent()
{
    view->setTimeBar(60);
}

void setup()
{
    delay(2000);
    view = new View(lcd, diodes, buzzer);
    UNITY_BEGIN();
    RUN_TEST(shouldInitializeGameScreen);
    RUN_TEST(shouldSetScoreTo1000);
    RUN_TEST(shouldSetMultiplierTo5);
    RUN_TEST(shouldAddMistakeMark1Then2);
    RUN_TEST(shouldSetTimeBarTo60Percent);
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