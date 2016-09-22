#ifndef DEBOUNCEDBUTTON_H
#define DEBOUNCEDBUTTON_H

#include <stdint.h>

#define DEBOUNCECOUNT   5
#define DEBOUNCETIME   5

class DebouncedButton {
public:
    DebouncedButton(uint8_t pin, bool pullup=true);
    void update();
    bool isPressed();

private:
    uint8_t _pin;
    bool _pullup;
    uint8_t _count;
    unsigned long _last;
};

#endif
