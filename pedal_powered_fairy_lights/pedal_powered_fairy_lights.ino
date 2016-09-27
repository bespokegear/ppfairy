#include "Config.h"
#include "Heartbeat.h"
#include "LatchedButton.h"
#include "VoltMode.h"
#include "LoadControl.h"
#include "MemoryFree.h"
#include "PedalVoltage.h"
#include <Arduino.h>
#include <avr/wdt.h>

// See Config.h for pin and other configuration

// Global variables

Heartbeat* heartbeat;
LatchedButton* resetButton;
LatchedButton* modeButton;
LoadControl* loadControl;
Mode* mode = NULL;

unsigned long lastLoop = 0;

enum eModes {
    Volt,
    Cap
};
eModes nextMode = Volt;

void setNextMode()
{
#ifdef DEBUG
    int freeb4 = freeMemory();
#endif
    bool start = false;
    if (mode) {
        mode->stop();
        delete mode;
        mode = NULL;
        start = true;
    }
    switch (nextMode) {
    case Volt:
        mode = new VoltMode();
        nextMode = Cap;
        break;
    case Cap:
        mode = new VoltMode();
        nextMode = Volt;
        break;
    }
    if (start) {
        mode->start();
    }
#ifdef DEBUG
    Serial.print(F("setNextMode() free b4/now: "));
    Serial.print(freeb4);
    Serial.print(F("/"));
    Serial.println(freeMemory());
#endif
}

void setup()
{
    Serial.begin(115200);

    // Use external reference
    analogReference(EXTERNAL);

    // Set up the blinker
    heartbeat = new Heartbeat(HEARTBEAT_LED_PIN);

    // Make an object for performing load control
    loadControl = new LoadControl();

    // Construct input buttons (sets pin modes in constructor)
    resetButton = new LatchedButton(RESET_BUTTON_PIN);
    modeButton = new LatchedButton(MODE_BUTTON_PIN);

    // Ensure load is disconnected at start, indicator off
    pinMode(INDICATOR_LED_PIN, OUTPUT);
    digitalWrite(INDICATOR_LED_PIN, LOW);

    // Let things settle
    delay(500);

    // enable watchdog reset at 1/4 sec
    wdt_enable(WDTO_250MS);

    // engage game mode
    setNextMode();

#ifdef DEBUG
    Serial.println(F("setup() E"));
#endif
}

void loop()
{
    // feed the watchdog
    wdt_reset();

#ifdef DEBUGTIME
    Serial.print(F("looptime="));
    Serial.println(millis() - lastLoop);
    lastLoop = millis();
#endif

#ifdef DEBUGMEM
    Serial.print(F("free="));
    Serial.println(freeMemory());
#endif

    // give a time slice to various peripheral functions
    heartbeat->update();
    loadControl->update();
    resetButton->update();
    modeButton->update();
    PedalVoltage.update();

    // detect button presses and behave appropriately
    if (resetButton->wasPressed()) {
#ifdef DEBUG
        Serial.println(F("BUTTON: resetting mode"));
#endif
        mode->reset();
    }

    if (modeButton->wasPressed()) {
#ifdef DEBUG
        Serial.println(F("BUTTON: switching mode"));
#endif
        setNextMode();
    }

    mode->update();
}

