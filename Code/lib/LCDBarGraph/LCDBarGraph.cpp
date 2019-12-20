#include "LCDBarGraph.h"

LCDBarGraph::LCDBarGraph(LiquidCrystal_I2C &lcd, int row, int column, int length)
    : lcd(lcd), row(row), column(column)
{
    totalBars = length * 5;
    for (size_t i = 0; i <= 5; i++)
        lcd.createChar(i, bars[i]);
}

void LCDBarGraph::drawBarGraph(float percentageFill)
{
    int barsToDraw = (int)(totalBars * percentageFill / 100);
    for (size_t i = 0; i < totalBars / 5; i++)
    {
        lcd.setCursor(column + i, row);
        lcd.write(' ');
    }
    for (size_t i = 0; i < barsToDraw / 5; i++)
    {
        lcd.setCursor(column + i, row);
        lcd.write(5);
    }
    lcd.setCursor(column + barsToDraw / 5, row);
    lcd.write(barsToDraw % 5);
}
