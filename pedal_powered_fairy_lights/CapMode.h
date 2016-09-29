#pragma once

#include "Config.h"
#include "Mode.h"

class CapMode : public Mode {
public:
    CapMode();
              
    virtual void start() {;}
    virtual void stop() {;}
    virtual void reset();
    virtual void modeUpdate();
    virtual void startFlare();

private:
    bool _inFlare;

};

