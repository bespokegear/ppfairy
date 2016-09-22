#include "Util.h"
#include <Arduino.h>

float analogToVoltage(const uint8_t pin)
{
    return (analogRead(pin)*3.3*570*100) / (1024*10);
}

