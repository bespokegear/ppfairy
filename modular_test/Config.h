#ifndef CONFIG_H
#define CONFIG_H

// LED strip parameters
#define NEOPIXEL_TYPE           (NEO_GRB + NEO_KHZ800)
#define NUMBER_OF_PIXELS        288
#define NEOPIXEL_PIN            4

// ChunkFill parameters
#define PIXEL_COLOR             0xff500a
// in 100ths of a volt:
#define VoltageMin              1000
// in 100ths of a volt:
#define VoltageMax              1600
#define IncrementTime           (VoltageMax - VoltageMin)

// General PIN config
#define VoltagePin              A0

/*

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
*/

#endif
