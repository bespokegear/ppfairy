#pragma once

class Flare {
public:
    // called periodically from loop()
    // Should execute quickly, update the LED strip and return
    virtual ~Flare() {;}
    virtual void update() = 0;

};
