#pragma once

class Mode {
public:
    Mode() {;}
    virtual ~Mode() {;}

    // All Modes must also implement a start() function
    virtual void start() = 0;

    // All Modes must also implement a stop() function
    virtual void stop() = 0;

    // Optionally over-ride reset
    virtual void reset() { start(); }

    // All Modes must implement an update() function
    // return true if the mode is running OK, false if it has quit
    virtual bool update() = 0;

};

