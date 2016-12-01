#pragma once

#include <stdint.h>
#include "Flare.h"
#include "Config.h"

class SpurtBlob {
public:
    SpurtBlob();
    void fire(uint32_t color, float velocity);
    void draw();
    const bool active() { return _location < NUMBER_OF_LEDS; }

private:
    uint32_t _color;
    float _velocity;
    float _location;
};
    
class Spurt : public Flare {
public:
    Spurt();
    virtual ~Spurt();
    void update();
    void fire(uint8_t slot);

private:
    SpurtBlob _spurts[FLARE_SPURT_COUNT];
};

