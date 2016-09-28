#include "SlowFill.h"
#include "Config.h"
#include "Debug.h"
#include "LEDs.h"

SlowFill::SlowFill(uint32_t color, float duration) :
    _color(color),
    _duration(duration),
    _percent(0.)
{
    _lastUpdate = 0;
    DBLN("SlowFill::SlowFill()");
}

void SlowFill::update()
{
    DBLN("SlowFill::update()");
    // First update don't do anything except set _lastUpdate
    if (_lastUpdate == 0) {
        _lastUpdate = millis();
        return;
    }

    // Don't do anything if we're already filled
    if (_percent >= 1.) { return; }

    // For subsequent updates, calculate how long has elapsed since the last call
    float elapsedSinceLastUpdate = (millis() - _lastUpdate) / 1000.;
    _lastUpdate = millis();

    // increment _percent by an amount depending on how many pixels we have
    // and the elapsed time. Note: percent expressed as 0 - 1
    _percent += NUMBER_OF_PIXELS * elapsedSinceLastUpdate / _duration;
    DBLN(_percent);

    display();
}

void SlowFill::reset()
{
    _percent = 0.;
    display();
}

void SlowFill::display()
{
    DBLN("SlowFill::display()");
    for (uint16_t i=0; i<=NUMBER_OF_PIXELS*_percent; i++) {
        LEDs.setPixelColor(i, _color);
    }
}

