#pragma once

#include <Arduino.h>

// LED strip parameters
#define NUMBER_OF_LEDS              60

// This is for initialising the Adafruit_NeoPixel library
// and will depend on the LED type.  Choose one of the following
// Diffuse RGB / Original strips:
#define NEOPIXEL_TYPE               (NEO_GRB + NEO_KHZ800)
// Triple pixel strip
//#define NEOPIXEL_TYPE               (NEO_BRG + NEO_KHZ800)

// Brightness is a range of 0-255, 255 being brightest
// It will set the brightness in all display modes
#define LED_BRIGHTNESS              255

// This is used to compensate for the time it takes to write to 
// the LEDs - without it, longer strips would take longer to 
// fill based on the VOLT_MODE_FASTEST_SEC setting.  Determined
// by trial and error
#define LED_SPEED_FACTOR            180

// General config
#define LED_DATA_PIN                4
#define PEDAL_VOLTAGE_PIN           A0
#define PEDAL_VOLTAGE_R1            10
#define PEDAL_VOLTAGE_R2            560
#define CAP_VOLTAGE_PIN             A1
#define CAP_VOLTAGE_R1              10
#define CAP_VOLTAGE_R2              150
#define RESET_BUTTON_PIN            2
#define MODE_BUTTON_PIN             3
#define HEARTBEAT_LED_PIN           13
#define INDICATOR_LED_PIN           9
#define PWM_LOAD_PIN                5
#define VPWMSETPOINT                3500 
#define VPWMHYSTERESIS              500
#define BROWNOUT_HIGH               1300
#define BROWNOUT_LOW                1200
#define LOAD_CONTROL_PERIOD_MS      25
#define VOLTAGE_SAMPLES             20

// VoltMode parameters
#define VOLT_MODE_COLOR_ON          0xFF500AUL
#define VOLT_MODE_COLOR_OFF         0x000000UL
// in 100ths of a volt:
#define VOLT_MODE_VMIN              1300
// in 100ths of a volt:
#define VOLT_MODE_VMAX              2500
// range 0.0= cubic, 1.0=totally linear
#define VOLT_MODE_LINEARITY         0.5
#define VOLT_MODE_FASTEST_SEC       5.0
#define VOLT_MODE_EEPROM_OFFSET     0

// CapMode parameters
#define CAP_MODE_LOW_VOLTS          1200
#define CAP_MODE_HIGH_VOLTS         1320

// Params for flare modes
#define FLARE_TYPE_COUNT            5
//#define FLARE_SEQUENTIAL            1

// Flare mode specific params
#define FLARE_RAINBOW_DELAY_MS      5
// Higher values = sparse sparkles
#define FLARE_SPARKLE_DARKENING     30
#define FLARE_SPURT_COUNT           (NUMBER_OF_LEDS/20)
// Increase this to have spurts appear less often
#define FLARE_SPURT_DELAY           200
// How fast the spurts go (is random in range defined by these two values):
#define FLARE_SPURT_VEL_MIN         (NUMBER_OF_LEDS/30)
#define FLARE_SPURT_VEL_MAX         NUMBER_OF_LEDS
// How many pixels between color changes
#define FLARE_CHASE_CHUNKSIZE       5
// How long to wait between pixel shifts
#define FLARE_CHASE_DELAY_MS        30
// How long to wait between pixel shifts in ColorFill mode
#define FLARE_COLORFILL_DELAY_MS    10

