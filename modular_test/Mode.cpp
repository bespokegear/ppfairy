#pragma once

class Mode {
public:
    Mode() {;}
    virtual ~Mode() {;}

    // All Modes must implement an update() function
    // return true if the mode is running OK, false if it has quit
    virtual bool update() = 0;

    // All Modes must also implement a brownout() function
    virtual void brownout() = 0;

};

