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
    Serial.println(F("VoltMode start"));
#endif
    DisplayMode::start();
    _lastPixel = 0;
    _timeLeft = IncrementTime;
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
    uint16_t vIn = analogToVoltage(VoltagePin);
    Serial.print(F("vIn="));
    Serial.print(vIn);
    if (vIn < VOLT_MODE_VMIN) {
        vIn = VOLT_MODE_VMIN;
    } else if (vIn > VOLT_MODE_VMAX) {
        vIn = VOLT_MODE_VMAX;
    }
    Serial.print(F(", clipped="));
    Serial.print(vIn);
    vIn -= VOLT_MODE_VMIN;
    Serial.print(F(", adjust="));
    Serial.println(vIn);

    if (_timeLeft > vIn) {
        _timeLeft -= vIn;
    } else if (_lastPixel < _pixels.numPixels()) {
        _lastPixel++;
        _pixels.setPixelColor(_lastPixel, PIXEL_COLOR);
        _pixels.show();
        _timeLeft = IncrementTime;
    }
    
    return true;
}


