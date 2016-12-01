#include "Chase.h"
#include "Config.h"
#include "LEDs.h"
#include <Arduino.h>

Chase::Chase(uint16_t chunkSize, unsigned long delay) :
    _chunkSize(chunkSize),
    _delay(delay)
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
    _color = (random(256)<<16) + (random(256)<<8) + random(256);
    _chunkCounter = _chunkSize;
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


