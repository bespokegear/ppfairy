#include "DisplayMode.h"

DisplayMode::DisplayMode(const uint16_t numPixels,
                         const uint8_t pixelPin,
                         neoPixelType pixelType) :
    _pixels(numPixels, pixelPin, pixelType)
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

