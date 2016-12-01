#include "Sparkle.h"
#include "Config.h"
#include "LEDs.h"
#include <Arduino.h>

Sparkle::Sparkle()
{
}

Sparkle::~Sparkle()
{
    LEDs.clear();
    LEDs.show();
}

void Sparkle::update()
{
    display();
}

void Sparkle::display()
{
    uint16_t i = random(0, NUMBER_OF_LEDS);
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
    switch (random(15+FLARE_SPARKLE_DARKENING)) {
    case 0:
        g = 220;
        break;
    case 1:
        r = 220;
        break;
    case 2:
    case 3:
    case 4:
        r = 80;
        g = 128;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        r = 30;
        g = 70;
        b = 205;
        break;
    default:
        r = 0;
        g = 0;
        b = 0;
    }

    LEDs.setPixelColor(i, r, g, b);
    r /= 3;
    g /= 3;
    b /= 3;
    if (i > 0) LEDs.setPixelColor(i-1, r, g, b);
    if (i < NUMBER_OF_LEDS-1) LEDs.setPixelColor(i+1, r, g, b);

    for(i=0; i<NUMBER_OF_LEDS; i++) {
        const uint32_t color = LEDs.getPixelColor(i);
        r = color >> 16;
        g = (color - r) >> 8;
        b = color % 256;
        if (r > 0) r--;
        if (g > 0) g--;
        if (b > 0) b--;
        LEDs.setPixelColor(i, r, g, b);
    }
    LEDs.show();
}

