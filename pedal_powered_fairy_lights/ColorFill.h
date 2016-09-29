#pragma once

#include "Flare.h"
#include <stdint.h>

class ColorFill : public Flare {
public:
    ColorFill();
    virtual ~ColorFill();
    void update();
    bool finished();

private:
    uint32_t _color;
    float _percent;
    unsigned long _lastUpdate;

    void reset();
    void display();
};
