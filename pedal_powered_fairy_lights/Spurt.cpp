#include "Spurt.h"
#include "Config.h"
#include "LEDs.h"
#include <Arduino.h>

SpurtBlob::SpurtBlob() : 
    _location(NUMBER_OF_LEDS)
{
}

void SpurtBlob::fire(uint32_t color, float velocity)
{
    _color = color;
    _velocity = velocity;
    _location = 0.0;
}

void SpurtBlob::draw() 
{
    if (active()) {
        // get the current RGB values for existing pixel and this SpurtBlob
        uint32_t color = LEDs.getPixelColor((uint16_t)_location);
        uint8_t cr = color >> 16;
        uint8_t cg = (color - cr) >> 8;
        uint8_t cb = color % 256;
        uint8_t br = _color >> 16;
        uint8_t bg = (_color - br) >> 8;
        uint8_t bb = _color % 256;

        // Set the new pixel RGB as the max of the existing and SpurtBlob colors
        // This is a very primative form of mixing I guess!
        LEDs.setPixelColor((uint16_t)_location, 
            cr > br ? cr : br,
            cg > bg ? cg : bg,
            cb > bb ? cb : bb);
        _location += _velocity;
    }
}   

Spurt::Spurt()
{
}

Spurt::~Spurt()
{
    LEDs.clear();
    LEDs.show();
}

void Spurt::update()
{
    // fade all pixels
    uint8_t r;
    uint8_t g;
    uint8_t b;
    for(uint16_t i=0; i<NUMBER_OF_LEDS; i++) {
        const uint32_t color = LEDs.getPixelColor(i);
        r = color >> 16;
        g = (color - r) >> 8;
        b = color % 256;
        if (r > 0) r--;
        if (g > 0) g--;
        if (b > 0) b--;
        LEDs.setPixelColor(i, r, g, b);
    }

    // update active spurts, and determine active count
    uint8_t count = 0;
    int8_t inactiveIdx = 0;
    for (uint8_t i=0; i<SPURT_COUNT; i++) {
        if (_spurts[i].active()) {
            count++;
        } else {
            // if any inactive, we mark the last one for possible use
            inactiveIdx = i;
        }
    }

    // decide if we want to start a new spurt
    if (count < SPURT_COUNT) {
        if (random(SPURT_PROBABILITY) == 0) {
            r = random(256);
            g = random(256);
            b = random(256);
            uint32_t col = (r<<16) + (g<<8) + b;
            float vel = random(3, 100)/1000.;
#ifdef DEBUGFLARE
            Serial.print(F("FIRE col=0x"));
            Serial.print(col, HEX);
            Serial.print(F(" vel="));
            Serial.println(vel, 5);
#endif
            _spurts[inactiveIdx].fire(col, vel);
        }
    }

    // plot active spurts
    for (uint8_t i=0; i<SPURT_COUNT; i++) {
        _spurts[i].draw();
    }

    LEDs.show();

}


