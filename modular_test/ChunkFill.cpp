#include "ChunkFill.h"
#include "Util.h"
#include <Arduino.h>

ChunkFill::ChunkFill() :
    DisplayMode(),
    _lastPixel(0)
{
}

void ChunkFill::start()
{
#ifdef DEBUG
    Serial.println(F("ChunkFill start"));
#endif
    DisplayMode::start();
    _lastPixel = 0;
    _timeLeft = IncrementTime;
}

void ChunkFill::stop()
{
#ifdef DEBUG
    Serial.print(F("ChunkFill stop"));
#endif
    _lastPixel = 0;
    DisplayMode::stop();
}

bool ChunkFill::update()
{
    uint16_t vIn = analogToVoltage(VoltagePin);
    Serial.print(F("vIn="));
    Serial.print(vIn);
    if (vIn < VoltageMin) {
        vIn = VoltageMin;
    } else if (vIn > VoltageMax) {
        vIn = VoltageMax;
    }
    Serial.print(F(", clipped="));
    Serial.print(vIn);
    vIn -= VoltageMin;
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


