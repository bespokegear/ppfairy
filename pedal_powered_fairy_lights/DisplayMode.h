#pragma once

#include "Config.h"
#include "Mode.h"
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class DisplayMode : public Mode {
public:
    // Note: takes params from NEOPIXEL_TYPE, NUMBER_OF_PIXELS, NEOPIXEL_PIN #defines
    DisplayMode();
    virtual ~DisplayMode();
    virtual void start();
    virtual void stop();

protected:
    Adafruit_NeoPixel _pixels;

    void resetPixels();

};

