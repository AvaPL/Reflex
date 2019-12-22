#pragma once

class Range
{

private:
    int lowerBound;
    int upperBound;

public:
    /**
     * @param lowerBound - lower bound (inclusive).
     * @param upperBound - upper bound (inclusive).
     */
    Range(int lowerBound, int upperBound)
        : lowerBound(lowerBound), upperBound(upperBound) {}
    bool containsValue(int value) const;
    int getLowerBound() const;
    void setLowerBound(int value);
    int getUpperBound() const;
    void setUpperBound(int value);
};
