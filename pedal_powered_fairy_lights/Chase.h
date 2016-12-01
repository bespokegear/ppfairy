#pragma once

#include "Flare.h"
#include <stdint.h>

class Chase : public Flare {
public:
    Chase(uint16_t chunkSize, unsigned long delay);
    virtual ~Chase();
    void update();

private:
    uint16_t _chunkSize;
    unsigned long _delay;
    uint32_t _color;
    uint16_t _chunkCounter;
    unsigned long _lastUpdate;

    void display();
    void newColor();
};
