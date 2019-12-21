#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDBarGraph
{

private:
    LiquidCrystal_I2C &lcd;
    int row;
    int column;
    int totalBars;
    int currentlyDrawnBars;

    byte bars[6][8]{
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

public:
    LCDBarGraph(LiquidCrystal_I2C &lcd, int row, int column, int length);
    void drawBarGraph(float percentageFill);

private:
    void clear();
    void drawAdditionalBars(int barsToDraw);
    void clearSpareBars(int barsToDraw);
};
