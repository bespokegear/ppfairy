#ifndef DISPLAYMODE_H
#define DISPLAYMODE_H

#include "Mode.h"
#include <stdint.h>
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

class DisplayMode : public Mode {
public:
    DisplayMode(const uint16_t numPixels, // number of LEDs in strip
                const uint8_t pixelPin,   // pin LED strip is connected to,
                neoPixelType pixelType);  // neopixel init flags
    virtual ~DisplayMode();
    virtual void start();
    virtual void stop();

protected:
    Adafruit_NeoPixel _pixels;

    void resetPixels();

};

#endif
