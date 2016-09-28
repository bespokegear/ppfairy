#pragma once

#include "Flare.h"
#include <stdint.h>

class SlowFill : public Flare {
public:
    SlowFill(uint32_t color, float duration);
    void update();

private:
    uint32_t _color;
    float _duration;
    float _percent;
    unsigned long _lastUpdate;

    void reset();
    void display();
};
