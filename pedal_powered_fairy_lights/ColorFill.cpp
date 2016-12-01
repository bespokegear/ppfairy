#include "ColorFill.h"
#include "Config.h"
#include "LEDs.h"
#include <Arduino.h>

ColorFill::ColorFill()
{
    _lastUpdate = 0;
    reset();
}

ColorFill::~ColorFill()
{
}

void ColorFill::update()
{
    // First update don't do anything except set _lastUpdate
    if (_lastUpdate == 0) {
        _lastUpdate = millis();
        return;
    }

    // Set a new color
    if (_percent >= 1.) { 
        reset(); 
        return; 
    }

    // For subsequent updates, calculate how long has elapsed since the last call
    float elapsedSinceLastUpdate = (millis() - _lastUpdate) / 1000.;
    _lastUpdate = millis();

    // increment _percent by an amount depending on how many pixels we have
    // and the elapsed time. Note: percent expressed as 0 - 1
    _percent += elapsedSinceLastUpdate / FLARE_COLOR_FILL_DURATION;

    display();
}

void ColorFill::reset()
{
    _color =  random(0,255) << 16;
    _color += random(0,255) << 8;
    _color += random(0,255);
    _percent = 0.;
#ifdef DEBUGFLARE
    Serial.print(F("ColorFill new color: 0x"));
    Serial.println(_color, HEX);
#endif
    display();
}

void ColorFill::display()
{
    for (uint16_t i=0; i<=NUMBER_OF_LEDS*_percent; i++) {
        if (i<=NUMBER_OF_LEDS*_percent) {
            LEDs.setPixelColor(i, _color);
        } else {
            LEDs.setPixelColor(i, 0x000000);
        }
    }
    LEDs.show();
}

