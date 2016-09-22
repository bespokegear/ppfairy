#include "DisplayMode.h"

DisplayMode::DisplayMode() :
    _pixels(NUMBER_OF_PIXELS, NEOPIXEL_PIN, NEOPIXEL_TYPE)
{
    _pixels.begin();
    _pixels.show();  // display unlit pixels (clears previous display)
}

DisplayMode::~DisplayMode()
{
    resetPixels();
}

void DisplayMode::start()
{
    resetPixels();   
}

void DisplayMode::stop()
{
    resetPixels();   
}

void DisplayMode::resetPixels()
{
    _pixels.clear();
    _pixels.show();
}

