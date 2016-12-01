#pragma once

#include <stdint.h>
#include "Flare.h"
#include "Config.h"

#define SPURT_COUNT         4
// Higher means less frequent
#define SPURT_PROBABILITY   300
#define SPURT_VEL_MIN       3
#define SPURT_VEL_MAX       100

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

private:
    SpurtBlob _spurts[SPURT_COUNT];
};

