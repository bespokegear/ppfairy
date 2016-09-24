#pragma once

#include "Config.h"
#include "DisplayMode.h"
#include <stdint.h>

class VoltMode : public DisplayMode {
public:
    VoltMode();
              
    virtual void start();
    virtual void stop();
    virtual bool update();

private:
    uint16_t _lastPixel;
    uint16_t _timeLeft;
};

