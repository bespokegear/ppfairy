#ifndef CHUNKFILL_H 
#define CHUNKFILL_H

#include "DisplayMode.h"
#include <stdint.h>

class ChunkFill : public DisplayMode {
public:
    ChunkFill(const uint16_t numPixels,      // number of LEDs in strip
              const uint8_t pixelPin,        // pin LED strip is connected to,
              neoPixelType pixelType,        // neopixel init flags
              const uint16_t numChunks,      // number of chunks strip is divided into
              const uint16_t millisPerChunk, // number of millis ontime to increment chunk
              const uint8_t vPin,            // pin to measure voltage on
              const float vThresh);          // threshold "on" value
              
    virtual bool update();

private:
    Adafruit_NeoPixel pixels;
    uint16_t _numChunks;
    uint16_t _millisPerChunk;
    uint8_t _vPin;
    float _vThresh;
    uint16_t _currentChunk;
    unsigned long _lastIncrement;

    // Increment how many chunks are set and return true when all are full
    bool incrementChunk();
    void reset();
    uint32_t getChunkColor(uint16_t chunk, bool on=true);
};

#endif
