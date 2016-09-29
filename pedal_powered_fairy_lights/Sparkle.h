#pragma once

#include "Flare.h"
#include <stdint.h>

class Sparkle : public Flare {
public:
    Sparkle();
    virtual ~Sparkle();
    void update();

private:
    void display();
};
