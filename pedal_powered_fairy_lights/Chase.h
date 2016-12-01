#pragma once

#include "Flare.h"
#include <stdint.h>

class Chase : public Flare {
public:
    Chase();
    virtual ~Chase();
    void update();

private:
    uint32_t _color;
    uint8_t _chunkCounter;
    unsigned long _lastUpdate;

    void display();
    void newColor();
};
