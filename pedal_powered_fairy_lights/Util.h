#pragma once

#include <stdint.h>

float highVoltageConversion(const uint8_t pin);
float voltageConversion(const uint8_t pin, const uint16_t r1KOhm, const uint16_t r2KOhm);
float calculateLinearity(float percent, float linearity);

