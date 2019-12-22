#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDBarGraph
{

private:
    static byte BARS[6][8];

private:
    LiquidCrystal_I2C &lcd;
    int row;
    int column;
    int totalBars;
    int currentlyDrawnBars;

public:
    /**
     * @param lcd - LCD that is already initialized.
     */
    LCDBarGraph(LiquidCrystal_I2C &lcd, int row, int column, int length);
    void drawBarGraph(float percentageFill);
    void clear();

private:
    void drawAdditionalBars(int barsToDraw);
    void clearSpareBars(int barsToDraw);
};
