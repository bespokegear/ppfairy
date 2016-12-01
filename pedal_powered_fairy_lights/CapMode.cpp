#include "CapMode.h"
#include "Util.h"
#include "CapVoltage.h"
#include "LEDs.h"
#include "ColorFill.h"
#include "Sparkle.h"
#include "Rainbow.h"
#include "Spurt.h"
#include <Arduino.h>

CapMode::CapMode() :
    _inFlare(false)
{
#ifdef DEBUG
    Serial.print(F("CapMode::CapMode(), capPin="));
    Serial.println(CapVoltage.getPin());
#endif
    _flare = NULL;
#ifdef SEQUENTIAL_FLARES
    _last_flare_id = 0;
#endif
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
#ifdef SEQUENTIAL_FLARES
    uint8_t flare_id = (_last_flare_id+1) % FLARE_TYPE_COUNT;
    _last_flare_id = flare_id;
#else
    uint8_t flare_id = random(FLARE_TYPE_COUNT);
#endif
    switch (flare_id) {
    case 0:
        _flare = new Sparkle();
        break;
    case 1:
        _flare = new Rainbow();
        break;
    case 2:
        _flare = new Spurt();
        break;
    default:
        _flare = new ColorFill();
        break;
    }
    _inFlare = true;
}

