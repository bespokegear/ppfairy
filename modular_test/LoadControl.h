#ifndef LOADCONTROL_H
#define LOADCONTROL_H

#include "Config.h"
#include "Mode.h"

class LoadControl : public Mode {
public:
    LoadControl();
    virtual ~LoadControl() {;}
    virtual bool update();
    virtual void start() {;}
    virtual void stop() {;}

private:
    long PWM1value;
    long proportional;
    long integral;
    long error;
    float voltageV1;
    float voltageV2;

};

#endif

