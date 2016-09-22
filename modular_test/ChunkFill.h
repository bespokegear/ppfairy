#ifndef CHUNKFILL_H 
#define CHUNKFILL_H

#include "Config.h"
#include "DisplayMode.h"
#include <stdint.h>

class ChunkFill : public DisplayMode {
public:
    ChunkFill();
              
    virtual void start();
    virtual void stop();
    virtual bool update();

private:
    uint16_t _lastPixel;
    uint16_t _timeLeft;
};

#endif
