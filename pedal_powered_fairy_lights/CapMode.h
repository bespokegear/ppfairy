#pragma once

#include "Config.h"
#include "Mode.h"
#include "Flare.h"

class CapMode : public Mode {
public:
    CapMode();
              
    virtual void start();
    virtual void stop();
    virtual void reset();
    virtual void modeUpdate();
    virtual void startFlare();

private:
    bool _inFlare;
    Flare* _flare;
#ifdef SEQUENTIAL_FLARES
    uint8_t _last_flare_id;
#endif

};

