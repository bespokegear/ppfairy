#include "ChunkFill.h"
#include "Util.h"
#include <Arduino.h>

ChunkFill::ChunkFill(const uint16_t numPixels,
                     const uint8_t pixelPin,
                     neoPixelType pixelType,
                     const uint16_t incrementTime,
                     const uint8_t vPin,
                     const uint16_t vMin, 
                     const uint16_t vMax, 
                     const uint32_t color) :
    DisplayMode(numPixels, pixelPin, pixelType),
    _incrementTime(incrementTime),
    _vPin(vPin),
    _vMin(vMin),
    _vMax(vMax),
    _color(color),
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
    _timeLeft = _incrementTime;
}

void ChunkFill::stop()
{
#ifdef DEBUG
    Serial.print(F("ChunkFill stop"));
#endif
    DisplayMode::stop();
}

bool ChunkFill::update()
{
    uint16_t vIn = analogToVoltage(_vPin);
    Serial.print(F("vIn="));
    Serial.print(vIn);
    if (vIn < _vMin) {
        vIn = _vMin;
    } else if (vIn > _vMax) {
        vIn = _vMax;
    }
    Serial.print(F(", clipped="));
    Serial.print(vIn);
    vIn -= _vMin;
    Serial.print(F(", adjust="));
    Serial.println(vIn);

    if (_timeLeft > vIn) {
        _timeLeft -= vIn;
    } else if (_lastPixel < _pixels.numPixels()) {
        _lastPixel++;
        _pixels.setPixelColor(_lastPixel, _color);
        _pixels.show();
        _timeLeft = _incrementTime;
    }
    
    return true;
}


