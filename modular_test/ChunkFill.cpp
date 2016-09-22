#include "ChunkFill.h"
#include "Util.h"
#include <Arduino.h>

ChunkFill::ChunkFill(const uint16_t numPixels,
                     const uint8_t pixelPin,
                     neoPixelType pixelType,
                     const uint16_t numChunks,
                     const uint16_t millisPerChunk,
                     const uint8_t vPin,
                     const float vThresh) :
    DisplayMode(numPixels, pixelPin, pixelType),
    _numChunks(numChunks),
    _millisPerChunk(millisPerChunk),
    _vPin(vPin),
    _vThresh(vThresh),
    _currentChunk(0),
    _lastIncrement(0)
{
}

bool ChunkFill::update()
{
    float vIn = analogToVoltage(_vPin);
    bool win = false;
    Serial.print(vIn);
    Serial.print(" / ");
    Serial.println(_vThresh);
    if (vIn >= _vThresh) {
        Serial.print("WIN?    >> ");
        win = incrementChunk();
        Serial.println(win);
    }
    else {
        reset();
    }

    // TODO: check for win
    _pixels.show();
    if (win) {
        reset();
    }
    return win;
}

bool ChunkFill::incrementChunk()
{
    if (millis() < _lastIncrement + _millisPerChunk) {
        return _currentChunk>=_numChunks;
    }
    _lastIncrement = millis();
    _currentChunk++;
    Serial.print("incrementChunk, now: ");
    Serial.println(_currentChunk);
    for(uint16_t i=0; i<_pixels.numPixels(); i++) {
        uint16_t chunk = i / _numChunks;
        _pixels.setPixelColor(i, getChunkColor(chunk, chunk <= _currentChunk));
    }
    return _currentChunk>=_numChunks;
}

void ChunkFill::reset()
{
    Serial.println("reset");
    _pixels.clear();
    _currentChunk = 0;
}

uint32_t ChunkFill::getChunkColor(uint16_t chunk, bool on)
{
    if (!on) {
        return 0x000000;
    } else {
        return 0x000004 + (chunk*16);
    }
}
