#include <unity.h>
#include "Buzzer.h"

const byte BUZZER_PIN = 8;

Buzzer buzzer(BUZZER_PIN);

void playTone(unsigned int tone){
    buzzer.playTone(tone, 500);
    delay(1000);
}

void shouldPlayLowTone(){
    playTone(Buzzer::TONE_LOW);
}

void shouldPlayMediumTone(){
    playTone(Buzzer::TONE_MEDIUM);
}

void shouldPlayHighTone(){
    playTone(Buzzer::TONE_HIGH);
}

void setup(){
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(shouldPlayLowTone);
    RUN_TEST(shouldPlayMediumTone);
    RUN_TEST(shouldPlayHighTone);
    UNITY_END();
}

void loop(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}