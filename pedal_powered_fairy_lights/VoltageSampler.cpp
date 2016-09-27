#include "VoltageSampler.h"
#include "Util.h"
#include <string.h>

VoltageSampler::VoltageSampler(const uint8_t pin) :
    _pin(pin),
    _count(0),
    _idx(0),
    _lastAvg(0),
    _updated(false)
{
    memset((void*)_samples, 0, sizeof(uint16_t)*VOLTAGE_SAMPLES);
}

void VoltageSampler::update() {
    _samples[_idx] = highVoltageConversion(_pin);
    _count = _count >= VOLTAGE_SAMPLES ? VOLTAGE_SAMPLES : _count+1;
    _idx = (_idx + 1) % VOLTAGE_SAMPLES;
    _updated = true;
}

uint16_t VoltageSampler::get() {
    if (!_updated) {
        return _lastAvg;
    }
    uint32_t sum = 0;
    for(uint8_t i=0; i<_count; i++) {
        sum += _samples[i];
    }
    _lastAvg = (uint16_t)(sum / _count);
    _updated = false;
    return _lastAvg;
}

