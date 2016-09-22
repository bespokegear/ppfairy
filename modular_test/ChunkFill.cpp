#include "ChunkFill.h"
#include "Util.h"
#include <Arduino.h>

ChunkFill::ChunkFill(const uint16_t numPixels,
                     const uint8_t pixelPin,
                     neoPixelType pixelType,
                     const uint16_t numChunks,
                     const uint16_t millisPerChunk,
                     const uint8_t vPin,
                     const float vThresh, 
                     const uint8_t brightness) :
    DisplayMode(numPixels, pixelPin, pixelType),
    _numChunks(numChunks),
    _millisPerChunk(millisPerChunk),
    _vPin(vPin),
    _vThresh(vThresh),
    _currentChunk(0),
    _lastIncrement(0),
    _brightness(brightness)
{
}

void ChunkFill::start()
{
#ifdef DEBUG
    Serial.print(F("ChunkFill start bright="));
    Serial.println(_brightness);
#endif
    DisplayMode::start();
    _currentChunk = 0;
    _lastIncrement = 0;
}

void ChunkFill::stop()
{
#ifdef DEBUG
    Serial.print(F("ChunkFill stop pix="));
    Serial.println(_pixels.numPixels());
#endif
    DisplayMode::stop();
}

bool ChunkFill::update()
{
    float vIn = analogToVoltage(_vPin);
    bool win = false;
    //Serial.print(vIn);
    //Serial.print(" / ");
    //Serial.println(_vThresh);
    if (vIn >= _vThresh) {
        //Serial.print("WIN?    >> ");
        win = incrementChunk();
        //Serial.println(win);
    }
    else {
        reset();
    }

    // TODO: handle win properly
    _pixels.show();
    if (win) {
        reset();
    }
    return win;
}

bool ChunkFill::incrementChunk()
{
    if (millis() >= _lastIncrement + _millisPerChunk) {
        _lastIncrement = millis();
        _pixels.setPixelColor(_currentChunk++, getChunkColor(_currentChunk));
    }
    return _currentChunk>=_numChunks;
}

void ChunkFill::reset()
{
    //Serial.println("reset");
    _pixels.clear();
    _currentChunk = 0;
}

uint32_t ChunkFill::getChunkColor(uint16_t chunk, bool on)
{
    if (!on) {
        return 0x000000;
    } 
    uint16_t r=( 255          * _brightness ) / 256;
    uint16_t g=( 255          * _brightness ) / 256;
    //uint16_t b=((4+(chunk*4)) * _brightness ) / 256;
    uint16_t b=( 255          * _brightness ) / 256;
    uint32_t col = (r*0x10000) + (g*0x100) + b;
    return col;
}

