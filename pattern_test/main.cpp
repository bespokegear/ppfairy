#include "Debug.h"
#include "Config.h"
#include "SlowFill.h"
#include "LEDs.h"
#include "LatchedButton.h"
#include "Heartbeat.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <MemoryFree.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define RAINBOWCOLORS_N 6

const uint32_t rainbowColors[RAINBOWCOLORS_N] { 0x110000UL, 0x111100UL, 0x001100UL, 0x001111UL, 0x000011UL, 0x110011UL };
uint8_t ci = 0;
Flare* flare = NULL;
LatchedButton* button = NULL;
Heartbeat* heartbeat = NULL;

void slowFill(uint32_t color, uint8_t wait) {
    DB(F("slowFill: col="));
    DB(color, HEX);
    DB(F(", col=wait"));
    DBLN(wait);
    for (uint16_t i=0; i<NUMBER_OF_PIXELS; i++) {
        LEDs.setPixelColor(i, color);
        LEDs.show();
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
    button = new LatchedButton(3);
    heartbeat = new Heartbeat(HEARTBEAT_LED_PIN);
    LEDs.begin();
    LEDs.clear();
    LEDs.show(); // Initialize all pixels to 'off'
    DB(F("LEDs object @ "));
    DBLN((unsigned long)(&LEDs), HEX);
    delay(400);
}

void loop() {
    DB(F("free="));
    DBLN(freeMemory());
    button->update();
    heartbeat->update();
    if (flare == NULL) {
        flare = new SlowFill(rainbowColors[ci], 50.0);
        ci = (ci + 1) % RAINBOWCOLORS_N;
    }
    else {
        flare->update();
    }
    if (flare->finished()) {
        delete flare;
        flare = NULL;
    }
}

