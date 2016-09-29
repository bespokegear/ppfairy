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

bool ColorFill::finished()
{
    return _percent >= 1;
}

void ColorFill::reset()
{
#define VOLT_MODE_COLOR_ON_R        (((VOLT_MODE_ON_BASE_COLOR >> 16)*VOLT_MODE_BRIGHTNESS)/255)
#define VOLT_MODE_COLOR_ON_G        ((((VOLT_MODE_ON_BASE_COLOR >> 8)%255)*VOLT_MODE_BRIGHTNESS)/255)
#define VOLT_MODE_COLOR_ON_B        (((VOLT_MODE_ON_BASE_COLOR%255)*VOLT_MODE_BRIGHTNESS)/255)
#define VOLT_MODE_COLOR_ON          ((VOLT_MODE_COLOR_ON_R<<16)+(VOLT_MODE_COLOR_ON_G<<8)+(VOLT_MODE_COLOR_ON_B))
#define VOLT_MODE_COLOR_OFF_R       (((VOLT_MODE_OFF_BASE_COLOR >> 16)*VOLT_MODE_BRIGHTNESS)/255)
#define VOLT_MODE_COLOR_OFF_G       ((((VOLT_MODE_OFF_BASE_COLOR >> 8)%255)*VOLT_MODE_BRIGHTNESS)/255)
#define VOLT_MODE_COLOR_OFF_B       (((VOLT_MODE_OFF_BASE_COLOR%255)*VOLT_MODE_BRIGHTNESS)/255)
#define VOLT_MODE_COLOR_OFF         ((VOLT_MODE_COLOR_OFF_R<<16)+(VOLT_MODE_COLOR_OFF_G<<8)+(VOLT_MODE_COLOR_OFF_B))
    _color = (((random(0,255)*CAP_MODE_BRIGHTNESS) / 255) << 16);
    _color += (((random(0,255)*CAP_MODE_BRIGHTNESS) / 255) << 8);
    _color += ((random(0,255)*CAP_MODE_BRIGHTNESS) / 255);
    _percent = 0.;
    display();
}

void ColorFill::display()
{
    for (uint16_t i=0; i<=NUMBER_OF_PIXELS*_percent; i++) {
        if (i<=NUMBER_OF_PIXELS*_percent) {
            LEDs.setPixelColor(i, _color);
        } else {
            LEDs.setPixelColor(i, 0x000000);
        }
    }
    LEDs.show();
}

