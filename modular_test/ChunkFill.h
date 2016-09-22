#ifndef CHUNKFILL_H 
#define CHUNKFILL_H

#include "DisplayMode.h"
#include <stdint.h>

class ChunkFill : public DisplayMode {
public:
    ChunkFill(const uint16_t numPixels,      // number of LEDs in strip
              const uint8_t pixelPin,        // pin LED strip is connected to,
              neoPixelType pixelType,        // neopixel init flags
              const uint16_t incrementTime,  // amount of accumulated voltage a chunk takes to advance
              const uint8_t vPin,            // pin to measure voltage on
              const uint16_t vMin,           // minimum volts to use up chunkTime (in 100ths of a volt)
              const uint16_t vMax,           // maximum volts to use up chunkTime (in 100ths of a volt)
              const uint32_t color);         // color of "on" pixels
              
    virtual void start();
    virtual void stop();
    virtual bool update();
    void win();

private:
    Adafruit_NeoPixel pixels;
    uint16_t _incrementTime;
    uint8_t _vPin;
    uint16_t _vMin;
    uint16_t _vMax;
    uint32_t _color;
    uint16_t _lastPixel;
    uint16_t _timeLeft;
};

#endif
