#include "Config.h"
#include "LatchedButton.h"
#include "VoltMode.h"

#include <Arduino.h>

// See Config.h for pin and other configuration

// Other pin configuration
const uint8_t      SwitchPin = 8;
const uint8_t      PWMLoadPin = 5;
const uint8_t      IndicatorLEDPin = 9;    // LED on board
const uint8_t      ResetButtonPin = 2;     // SW1
const uint8_t      ModeButtonPin = 3;      // SW2

// Global variables
const uint8_t NumberOfModes = 1;
Mode* modes[NumberOfModes] = {NULL}; 
uint8_t currentModeId = NumberOfModes-1;

// Input buttons
LatchedButton* resetButton;
LatchedButton* modeButton;

void nextMode()
{
#ifdef DEBUG
    Serial.print(F("nextMode(), "));
    Serial.print(currentModeId);
    Serial.print(F(" -> "));
#endif
    modes[currentModeId]->stop();
    currentModeId  = (currentModeId + 1) % NumberOfModes;
#ifdef DEBUG
    Serial.println(currentModeId);
#endif
    modes[currentModeId]->start();
}

void setup()
{
    Serial.begin(115200);

    pinMode(PWMLoadPin, OUTPUT);
    pinMode(IndicatorLEDPin, OUTPUT);

    // Construct input buttons (sets pin modes in constructor)
    resetButton = new LatchedButton(ResetButtonPin);
    modeButton = new LatchedButton(ModeButtonPin);

    // Ensure load is disconnected at start, indicator off
    digitalWrite(PWMLoadPin, LOW);
    digitalWrite(IndicatorLEDPin, LOW);

    // Create a display mode
    modes[0] = new VoltMode();

    // Let things settle
    delay(500);

    nextMode();

#ifdef DEBUG
    Serial.println(F("setup() E"));
#endif
}

void loop()
{
    resetButton->update();

    if (resetButton->wasPressed()){
#ifdef DEBUG
        Serial.println(F("Reset pressed, swapping "));
#endif
        modes[currentModeId]->start();
    }

    modes[currentModeId]->update();
}

