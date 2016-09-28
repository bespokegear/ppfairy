#include "Debug.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <MemoryFree.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 4
#define LEDS 84
#define RAINBOWCOLORS_N 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN);
const uint32_t rainbowColors[RAINBOWCOLORS_N] { 0x110000UL, 0x111100UL, 0x001100UL, 0x001111UL, 0x000011UL, 0x110011UL };
uint8_t ci = 0;

void slowFill(uint32_t color, uint8_t wait) {
    DB(F("slowFill: col="));
    DB(color, HEX);
    DB(F(", col=wait"));
    DBLN(wait);
    for (uint16_t i=0; i<LEDS; i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
}

void setup() {
    Serial.begin(115200);
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) { 
        clock_prescale_set(clock_div_1);
    }
#endif
    // End of trinket special code
    strip.begin();
    strip.clear();
    strip.show(); // Initialize all pixels to 'off'
    delay(400);
}

void loop() {
    DB(F("ci="));
    DB(ci);
    DB(F(", free="));
    DBLN(freeMemory());
    slowFill(rainbowColors[ci], 1);
    ci = (ci + 1) % RAINBOWCOLORS_N;
}

