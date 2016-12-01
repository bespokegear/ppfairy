#include "CapMode.h"
#include "Util.h"
#include "CapVoltage.h"
#include "LEDs.h"
#include "Sparkle.h"
#include "Rainbow.h"
#include "Spurt.h"
#include "Chase.h"
#include <Arduino.h>

CapMode::CapMode() :
    _inFlare(false)
{
#ifdef DEBUG
    Serial.print(F("CapMode::CapMode(), capPin="));
    Serial.println(CapVoltage.getPin());
#endif
    _flare = NULL;
#ifdef FLARE_SEQUENTIAL
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
#ifdef FLARE_SEQUENTIAL
    uint8_t flare_id = (_last_flare_id+1) % FLARE_TYPE_COUNT;
    _last_flare_id = flare_id;
#else
    uint8_t flare_id = random(FLARE_TYPE_COUNT);
#endif
    switch (flare_id) {
    case 0:
#ifdef DEBUGFLARE
        Serial.println(F("Flare: Rainbow"));
#endif
        _flare = new Rainbow();
        break;
    case 1:
#ifdef DEBUGFLARE
        Serial.println(F("Flare: Sparkle"));
#endif
        _flare = new Sparkle();
        break;
    case 2:
#ifdef DEBUGFLARE
        Serial.println(F("Flare: Spurt"));
#endif
        _flare = new Spurt();
        break;
    case 3:
#ifdef DEBUGFLARE
        Serial.println(F("Flare: Chase"));
#endif
        _flare = new Chase(FLARE_CHASE_CHUNKSIZE, FLARE_CHASE_DELAY_MS);
        break;
    default:
#ifdef DEBUGFLARE
        Serial.println(F("Flare: ColorFill"));
#endif
        _flare = new Chase(NUMBER_OF_LEDS, FLARE_COLORFILL_DELAY_MS);
        break;
    }
    _inFlare = true;
}

