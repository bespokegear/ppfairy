#include <Arduino.h>
#include "ChunkFill.h"

const uint16_t NumberOfPixels = 24;
const uint8_t  PixelPin = 9;
const uint16_t NumberOfChunks = 4;
const uint16_t ChunkMillis = 500;
const uint8_t  VoltagePin = A0;
const uint8_t  SwitchPin = 8;
const float    ThresholdVoltage = 12.0;

Mode* m = NULL;

void setup()
{
    Serial.begin(115200);
    delay(500);
    m = new ChunkFill(NumberOfPixels, PixelPin, NEO_GRB + NEO_KHZ800, NumberOfChunks, ChunkMillis, VoltagePin, ThresholdVoltage);
    Serial.println("setup() E");
}

void loop()
{
    Serial.println("loop() S");
    m->update();
    delay(300);
    Serial.println("loop() E");
}

