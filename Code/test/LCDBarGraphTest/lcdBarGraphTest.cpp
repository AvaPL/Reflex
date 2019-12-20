#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <unity.h>
#include "LCDBarGraph.h"

const byte LCD_ADDRESS = 0x20;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

LCDBarGraph *lcdBarGraph; //Pointer, because of global variables initialization order.

void tearDown()
{
    delay(2000);
    lcd.clear();
}

void shouldDraw100PercentFillGraph()
{
    lcdBarGraph->drawBarGraph(100);
}

void shouldDraw50PercentFillGraph()
{
    lcdBarGraph->drawBarGraph(50);
}

void shouldDraw60PercentFillGraph()
{
    lcdBarGraph->drawBarGraph(60);
}

void shouldAllowWritingAdditionalCharacters()
{
    lcdBarGraph->drawBarGraph(80);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.write('X');
    delay(1000);
    lcdBarGraph->drawBarGraph(20);
}

void runTests()
{
    RUN_TEST(shouldDraw100PercentFillGraph);
    RUN_TEST(shouldDraw50PercentFillGraph);
    RUN_TEST(shouldDraw60PercentFillGraph);
    RUN_TEST(shouldAllowWritingAdditionalCharacters);
}

void setup()
{
    delay(2000);
    lcd.init();
    UNITY_BEGIN();
    lcdBarGraph = new LCDBarGraph(lcd, 1, 0, LCD_COLUMNS);
    runTests();
    delete lcdBarGraph;
    lcdBarGraph = new LCDBarGraph(lcd, 0, 1, LCD_COLUMNS - 2);
    runTests();
    delete lcdBarGraph;
    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}