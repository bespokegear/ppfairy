#pragma once

#include "Flare.h"
#include <stdint.h>

class Rainbow : public Flare {
public:
    Rainbow();
    virtual ~Rainbow();
    void update();

private:
    unsigned long _lastUpdate;
    uint16_t _pos;

    void display();
    uint32_t Wheel(uint8_t WheelPos);

};
