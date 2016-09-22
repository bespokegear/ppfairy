#include "VoltMode.h"
#include "Util.h"
#include <Arduino.h>

VoltMode::VoltMode() :
    DisplayMode(),
    _lastPixel(0)
{
}

void VoltMode::start()
{
#ifdef DEBUG
    Serial.print(F("VoltMode start, color:"));
    Serial.println(VOLT_MODE_COLOR, HEX);
#endif
    DisplayMode::start();
    _lastPixel = 0;
    _timeLeft = VOLT_MODE_TIME;
}

void VoltMode::stop()
{
#ifdef DEBUG
    Serial.print(F("VoltMode stop"));
#endif
    _lastPixel = 0;
    DisplayMode::stop();
}

bool VoltMode::update()
{
    uint16_t vIn = highVoltageConversion(PEDAL_VOLTAGE_PIN);
#ifdef DEBUG
    Serial.print(F("vIn="));
    Serial.print(vIn);
#endif
    if (vIn < VOLT_MODE_VMIN) {
        vIn = VOLT_MODE_VMIN;
    } else if (vIn > VOLT_MODE_VMAX) {
        vIn = VOLT_MODE_VMAX;
    }
#ifdef DEBUG
    Serial.print(F(", clipped="));
    Serial.print(vIn);
#endif
    vIn -= VOLT_MODE_VMIN;
#ifdef DEBUG
    Serial.print(F(", adjust="));
    Serial.println(vIn);
#endif

    if (_timeLeft > vIn) {
        _timeLeft -= vIn;
    } else if (_lastPixel < _pixels.numPixels()) {
        _pixels.setPixelColor(_lastPixel, VOLT_MODE_COLOR);
        _pixels.show();
        _lastPixel++;
        _timeLeft = VOLT_MODE_TIME;
    }
    
    return true;
}


