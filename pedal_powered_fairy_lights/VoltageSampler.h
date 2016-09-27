#pragma once

#include "Config.h"
#include <stdint.h>

class VoltageSampler {
public:
    VoltageSampler(const uint8_t pin);
    ~VoltageSampler() {;}

    void update();
    uint16_t get();

private:
    uint8_t _pin;
    uint8_t _count;
    uint8_t _idx;
    uint16_t _lastAvg;
    bool _updated;
    uint16_t _samples[VOLTAGE_SAMPLES];

};

