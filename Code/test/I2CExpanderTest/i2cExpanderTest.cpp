#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <unity.h>

void shouldDetectExpander()
{
    byte address = 0x20;
    Wire.beginTransmission(address);
    int status = Wire.endTransmission();
    TEST_ASSERT_EQUAL(0, status);
}

void setup()
{
    delay(2000);
    Wire.begin();
    UNITY_BEGIN();
    RUN_TEST(shouldDetectExpander);
    UNITY_END();
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}