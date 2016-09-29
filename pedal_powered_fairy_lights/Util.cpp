#include "Util.h"
#include <Arduino.h>

float highVoltageConversion(const uint8_t pin)
{
    return (analogRead(pin)*3.3*570*100) / (1024*10);
}

float voltageConversion(const uint8_t pin, const uint16_t r1KOhm, const uint16_t r2KOhm)
{
    return (analogRead(pin)*3.3*(r1KOhm+r2KOhm)*100) / (1024*r1KOhm);
}

float calculateLinearity(const float percent, const float linearity)
{
    float cube = percent * percent * percent;
    return cube+((percent-cube)*linearity);
}

