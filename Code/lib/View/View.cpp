#include "View.h"

View::View(LiquidCrystal_I2C &lcd, Diodes &diodes, Buzzer &buzzer) : lcd(lcd), diodes(diodes), buzzer(buzzer)
{
    lcd.init();
    diodes.turnOffAll();
}

void View::printWelcomeScreen()
{
    String topLine = "  Tester  ";
    String bottomLine = "Refleksu  ";
    lcd.clear();
    printAnimatedLines(topLine, bottomLine);
}

void View::View::printAnimatedLines(String topLine, String bottomLine)
{
    for (size_t i = 1; i <= 10; i++)
    {
        lcd.setCursor(0, 0);
        lcd.print(topLine.substring(topLine.length() - i, topLine.length()));
        lcd.setCursor(16 - i, 1);
        lcd.print(bottomLine.substring(0, i));
        delay(100);
    }
}

void View::printCountdown()
{
    lcd.clear();
    printCountdownNumber(5, 0, 0);
    printCountdownNumber(4, 3, 1);
    buzzer.playTone(Buzzer::TONE_LOW, 500);
    printCountdownNumber(3, 6, 0);
    buzzer.playTone(Buzzer::TONE_MEDIUM, 500);
    printCountdownNumber(2, 9, 1);
    buzzer.playTone(Buzzer::TONE_HIGH, 500);
    printCountdownNumber(1, 12, 0);
}

void View::View::printCountdownNumber(int number, byte column, byte row)
{
    String numberString = String(number);
    for (size_t i = 0; i < 4; i++)
    {
        lcd.setCursor(column, row);
        lcd.print(numberString);
        numberString += '.';
        delay(200);
    }
}

void View::printScore(long score, long highscore)
{
    char scoreString[17];
    snprintf(scoreString, 17, "Score:%10ld", score);
    char highscoreString[17];
    snprintf(highscoreString, 17, "Highscore:%6ld", highscore);
    lcd.clear();
    lcd.print(scoreString);
    lcd.setCursor(0, 1);
    lcd.print(highscoreString);
}

void View::printNewHighscore(long newHighscore)
{
    lcd.clear();
    lcd.print(" NEW HIGHSCORE! ");
    String newHighscoreString = String(newHighscore);
    lcd.setCursor(8 - newHighscoreString.length() / 2, 1);
    lcd.print(newHighscoreString);
}

LiquidCrystal_I2C &View::getLcd()
{
    return lcd;
}

Diodes &View::getDiodes()
{
    return diodes;
}

Buzzer &View::getBuzzer()
{
    return buzzer;
}
