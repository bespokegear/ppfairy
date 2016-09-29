#include "CapMode.h"
#include "Util.h"
#include "CapVoltage.h"
#include <Arduino.h>

CapMode::CapMode() :
    _inFlare(false)
{
#ifdef DEBUG
    Serial.print(F("CapMode::CapMode(), capPin="));
    Serial.println(CapVoltage.getPin());
#endif
}

void CapMode::reset()
{
#ifdef DEBUG
    Serial.println(F("CapMode::reset"));
#endif
    _inFlare = false;
    start();
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
}

void CapMode::startFlare()
{
#ifdef DEBUG
    Serial.println(F("CapMode::startFlare"));
#endif
    _inFlare = true;
}
