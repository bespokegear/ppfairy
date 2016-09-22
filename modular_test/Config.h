#ifndef CONFIG_H
#define CONFIG_H

// LED strip parameters
#define NEOPIXEL_TYPE           (NEO_GRB + NEO_KHZ800)
#define NUMBER_OF_PIXELS        288
#define NEOPIXEL_PIN            4

// VoltMode parameters
#define VOLT_MODE_COLOR         0xff500a
// in 100ths of a volt:
#define VOLT_MODE_VMIN          1000
// in 100ths of a volt:
#define VOLT_MODE_VMAX          1600
#define VOLT_MODE_TIME          (VOLT_MODE_VMAX - VOLT_MODE_VMIN)

// General config
#define PEDAL_VOLTAGE_PIN       A0
#define RESET_BUTTON_PIN        2
#define MODE_BUTTON_PIN         3
#define INDICATOR_LED_PIN       9
#define PWM_LOAD_PIN            5

#endif

