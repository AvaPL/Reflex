#include "LCDBarGraph.h"

byte LCDBarGraph::BARS[6][8]{
    {B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000,
     B00000},
    {B10000,
     B10000,
     B10000,
     B10000,
     B10000,
     B10000,
     B10000,
     B10000},
    {B11000,
     B11000,
     B11000,
     B11000,
     B11000,
     B11000,
     B11000,
     B11000},
    {B11100,
     B11100,
     B11100,
     B11100,
     B11100,
     B11100,
     B11100,
     B11100},
    {B11110,
     B11110,
     B11110,
     B11110,
     B11110,
     B11110,
     B11110,
     B11110},
    {B11111,
     B11111,
     B11111,
     B11111,
     B11111,
     B11111,
     B11111,
     B11111}};

LCDBarGraph::LCDBarGraph(LiquidCrystal_I2C &lcd, int row, int column, int length)
    : lcd(lcd), row(row), column(column)
{
    totalBars = length * 5;
    for (size_t i = 0; i <= 5; i++)
        lcd.createChar(i, BARS[i]);
    clear();
}

void LCDBarGraph::clear()
{
    for (int i = 0; i < totalBars / 5; i++)
    {
        lcd.setCursor(column + i, row);
        lcd.write(0);
    }
    currentlyDrawnBars = 0;
}

void LCDBarGraph::drawBarGraph(float percentageFill)
{
    if (percentageFill < 0 || percentageFill > 100)
        return;
    int barsToDraw = (int)(totalBars * percentageFill / 100);
    if (barsToDraw > currentlyDrawnBars)
        drawAdditionalBars(barsToDraw);
    else if (barsToDraw < currentlyDrawnBars)
        clearSpareBars(barsToDraw);
    currentlyDrawnBars = barsToDraw;
}

void LCDBarGraph::drawAdditionalBars(int barsToDraw)
{
    for (int i = currentlyDrawnBars / 5; i < barsToDraw / 5; i++)
    {
        lcd.setCursor(column + i, row);
        lcd.write(5);
    }
    lcd.setCursor(column + barsToDraw / 5, row);
    lcd.write(barsToDraw % 5);
}

void LCDBarGraph::clearSpareBars(int barsToDraw)
{
    for (int i = currentlyDrawnBars / 5; i >= barsToDraw / 5; i--)
    {
        lcd.setCursor(column + i, row);
        lcd.write(0);
    }
    lcd.setCursor(column + barsToDraw / 5, row);
    lcd.write(barsToDraw % 5);
}
