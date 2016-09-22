#include <Arduino.h>
#include "DebouncedButton.h"
#include "ChunkFill.h"

// LED strip details
const neoPixelType NeoPixelType = NEO_GRB + NEO_KHZ800;
const uint16_t     NumberOfPixels = 80;
const uint8_t      PixelPin = 6;

// ChunkFill mode settings
const uint16_t     NumberOfChunks = 8;
const uint16_t     ChunkMillis = 100;
const float        ThresholdVoltage = 12.0;

// Other pin configuration
const uint8_t      VoltagePin = A0;
const uint8_t      SwitchPin = 8;
const uint8_t      PWMLoadPin = 5;
const uint8_t      IndicatorLEDPin = 9; // LED on board
const uint8_t      ResetButtonPin = 2;  // SW1
const uint8_t      ModeButtonPin = 3;   // SW2

// Global variables
Mode* CurrentMode = NULL;    // Current game mode

// Input buttons
DebouncedButton* ResetButton;
DebouncedButton* ModeButton;

void setup()
{
    Serial.begin(115200);

    pinMode(PWMLoadPin, OUTPUT);
    pinMode(IndicatorLEDPin, OUTPUT);

    // Construct input buttons (sets pin modes in constructor)
    ResetButton = new DebouncedButton(ResetButtonPin);
    ModeButton = new DebouncedButton(ModeButtonPin);

    // Ensure load is disconnected at start, indicator off
    digitalWrite(PWMLoadPin, LOW);
    digitalWrite(IndicatorLEDPin, LOW);

    // Create a display mode
    CurrentMode = new ChunkFill(NumberOfPixels, PixelPin, NEO_GRB + NEO_KHZ800, NumberOfChunks, ChunkMillis, VoltagePin, ThresholdVoltage);

    // Let things settle
    delay(500);
}

void loop()
{
    ResetButton->update();
    ModeButton->update();

    // TODO: if Mode button pressed, swap mode
    // TODO: handle Reset Button

    CurrentMode->update();
}

