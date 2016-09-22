#ifndef LATCHEDBUTTON_H
#define LATCHEDBUTTON_H

#include "DebouncedButton.h"

class LatchedButton : public DebouncedButton {
public:
    LatchedButton(uint8_t pin, bool pullup=true);
    void update();
    bool wasPressed();

private:
    bool _pressed;
};

#endif
