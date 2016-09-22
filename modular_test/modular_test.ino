#include <Arduino.h>
#include "LatchedButton.h"
#include "ChunkFill.h"

// LED strip details
const neoPixelType NeoPixelType = NEO_GRB + NEO_KHZ800;
const uint16_t     NumberOfPixels = PIXELS;
const uint8_t      PixelPin = 4;

// ChunkFill mode settings
const uint16_t     NumberOfChunks = NumberOfPixels;
const uint16_t     VoltageMin = 1000;      // in 100ths of a volt
const uint16_t     VoltageMax = 1600;      // in 100ths of a volt
const uint16_t     IncrementTime = VoltageMax - VoltageMin;
const uint32_t     PixelColor = 0x403040;

// Other pin configuration
const uint8_t      VoltagePin = A0;
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
    modes[0] = new ChunkFill(NumberOfPixels, PixelPin, NEO_GRB + NEO_KHZ800, IncrementTime, VoltagePin, VoltageMin, VoltageMax, PixelColor);

    // Let things settle
    delay(500);

    nextMode();

#ifdef DEBUG
    Serial.println(F("setup() E"));
#endif
}

void loop()
{
    //resetButton->update();
    resetButton->update();

    if (resetButton->wasPressed()){
#ifdef DEBUG
        Serial.println(F("Reset pressed, swapping "));
#endif
        nextMode();
    }

    modes[currentModeId]->update();
}

