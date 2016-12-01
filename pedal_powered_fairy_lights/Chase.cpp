#include "Chase.h"
#include "Config.h"
#include "LEDs.h"
#include <Arduino.h>

Chase::Chase(uint16_t chunkSize, unsigned long delay) :
    _chunkSize(chunkSize),
    _delay(delay),
    _divider(false)
{
    newColor();
    _lastUpdate = millis();
}

Chase::~Chase()
{
    LEDs.clear();
    LEDs.show();
}

void Chase::newColor()
{
    uint32_t r = random(256)/(_divider?4:1);
    uint16_t g = random(256)/(_divider?4:1);
    uint8_t  b = random(256)/(_divider?4:1);
    _color = (r<<16) + (g<<8) + b;
    _chunkCounter = _chunkSize;
    _divider = !_divider;
}

void Chase::update()
{
    if (_lastUpdate + _delay > millis()) {
        return;
    }
    _lastUpdate = millis();

    if (_chunkCounter-- == 0) {
        newColor();
    }

    // Move existing colours along one pixel
    for (uint16_t i=NUMBER_OF_LEDS-1; i>0; i--) {
        LEDs.setPixelColor(i, LEDs.getPixelColor(i-1));
    }

    // Set first pixel to current pixel color
    LEDs.setPixelColor(0, _color);
    LEDs.show();
}


