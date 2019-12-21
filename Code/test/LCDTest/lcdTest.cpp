#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <unity.h>

const byte LCD_ADDRESS = 0x20;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void tearDown()
{
    delay(5000);
    lcd.clear();
}

void shouldPrintHelloWorld()
{
    lcd.print("Hello World!");
}

void shouldPrintTesterRefleksu()
{
    lcd.setCursor(2, 0);
    lcd.print("Tester");
    lcd.setCursor(6, 1);
    lcd.print("Refleksu");
}

void setup()
{
    delay(2000);
    lcd.init();
    UNITY_BEGIN();
    RUN_TEST(shouldPrintHelloWorld);
    RUN_TEST(shouldPrintTesterRefleksu);
    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}