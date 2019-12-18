#include "Range.h"

bool Range::containsValue(int value) const
{
    return lowerBound <= value && value <= upperBound;
}

int Range::getLowerBound() const
{
    return lowerBound;
}

void Range::setLowerBound(int value)
{
    lowerBound = value;
}

int Range::getUpperBound() const
{
    return upperBound;
}

void Range::setUpperBound(int value)
{
    upperBound = value;
}
