#include "CapMode.h"
#include "Util.h"
#include "CapVoltage.h"
#include "LEDs.h"
#include "ColorFill.h"
#include "Rainbow.h"
#include <Arduino.h>

CapMode::CapMode() :
    _inFlare(false)
{
#ifdef DEBUG
    Serial.print(F("CapMode::CapMode(), capPin="));
    Serial.println(CapVoltage.getPin());
#endif
    _flare = NULL;
}

void CapMode::reset()
{
#ifdef DEBUG
    Serial.println(F("CapMode::reset"));
#endif
    _inFlare = false;
    if (_flare) {
        delete _flare;
        _flare = NULL;
    }
    start();
}

void CapMode::start() 
{
    LEDs.clear();
    LEDs.show();
}

void CapMode::stop() 
{
    reset();
}

void CapMode::modeUpdate()
{
    uint16_t vIn = CapVoltage.get();
#ifdef DEBUGVIN
    Serial.print(F("Cap vIn="));
    Serial.println(vIn);
#endif
    if (!_inFlare && vIn >= CAP_MODE_HIGH_VOLTS) {
        startFlare();
    } else if (_inFlare && vIn < CAP_MODE_LOW_VOLTS) {
        reset();
    }
    if (_flare && _inFlare) {
        _flare->update();
    }
}

void CapMode::startFlare()
{
#ifdef DEBUG
    Serial.println(F("CapMode::startFlare"));
#endif
    if (_flare) {
        delete _flare;
    }
    // _flare = new ColorFill();
    switch (random(2)) {
    case 1:
        _flare = new Rainbow();
        break;
    default:
        _flare = new ColorFill();
        break;
    }
    _inFlare = true;
}

