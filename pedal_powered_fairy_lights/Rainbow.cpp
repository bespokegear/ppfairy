#include "Rainbow.h"
#include "Config.h"
#include "LEDs.h"

Rainbow::Rainbow() :
    _lastUpdate(0),
    _pos(0)
{
}

Rainbow::~Rainbow()
{
}

void Rainbow::update()
{
    uint16_t elapsed = millis() - _lastUpdate;
    if (elapsed < FLARE_RAINBOW_DELAY_MS) {
        return;
    }
    _lastUpdate = millis();
    display();
}

// Slightly different, this makes the rainbow equally distributed throughout
void Rainbow::display() {
#ifdef DEBUG
    Serial.print(F("Raindow::display, _pos="));
    Serial.println(_pos);
#endif
    for(uint16_t i=0; i<NUMBER_OF_LEDS; i++) {
        //LEDs.setPixelColor(i, Wheel((i+NUMBER_OF_LEDS) & 255));
        LEDs.setPixelColor(i, Wheel(((i * 256 / NUMBER_OF_LEDS) + _pos) & 255));
    }
    _pos++;
    LEDs.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Rainbow::Wheel(uint8_t WheelPos) 
{
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return LEDs.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return LEDs.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
    }
    WheelPos -= 170;
    return LEDs.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}


