#pragma once

// LED strip parameters
#define NEOPIXEL_TYPE               (NEO_GRB + NEO_KHZ800)
#define NUMBER_OF_PIXELS            288
#define NEOPIXEL_PIN                4

// VoltMode parameters
#define VOLT_MODE_ON_BASE_COLOR     0xFF500A
#define VOLT_MODE_OFF_BASE_COLOR    0x000000
// in a range of 0-255:
#define VOLT_MODE_BRIGHTNESS        255
// in 100ths of a volt:
#define VOLT_MODE_VMIN              1200
// in 100ths of a volt:
#define VOLT_MODE_VMAX              2500
#define VOLT_MODE_SLOWDOWN          20
#define VOLT_MODE_EEPROM_OFFSET     0

// These are calculated by the preprocessor, so don't use CPU or RAM...  :)
#define VOLT_MODE_TIME              ((VOLT_MODE_VMAX - VOLT_MODE_VMIN) * VOLT_MODE_SLOWDOWN)
#define VOLT_MODE_COLOR_ON_R        (((VOLT_MODE_ON_BASE_COLOR >> 16)*VOLT_MODE_BRIGHTNESS)/256)
#define VOLT_MODE_COLOR_ON_G        ((((VOLT_MODE_ON_BASE_COLOR >> 8)%256)*VOLT_MODE_BRIGHTNESS)/256)
#define VOLT_MODE_COLOR_ON_B        (((VOLT_MODE_ON_BASE_COLOR%256)*VOLT_MODE_BRIGHTNESS)/256)
#define VOLT_MODE_COLOR_ON          ((VOLT_MODE_COLOR_ON_R<<16)+(VOLT_MODE_COLOR_ON_G<<8)+(VOLT_MODE_COLOR_ON_B))
#define VOLT_MODE_COLOR_OFF_R       (((VOLT_MODE_OFF_BASE_COLOR >> 16)*VOLT_MODE_BRIGHTNESS)/256)
#define VOLT_MODE_COLOR_OFF_G       ((((VOLT_MODE_OFF_BASE_COLOR >> 8)%256)*VOLT_MODE_BRIGHTNESS)/256)
#define VOLT_MODE_COLOR_OFF_B       (((VOLT_MODE_OFF_BASE_COLOR%256)*VOLT_MODE_BRIGHTNESS)/256)
#define VOLT_MODE_COLOR_OFF         ((VOLT_MODE_COLOR_OFF_R<<16)+(VOLT_MODE_COLOR_OFF_G<<8)+(VOLT_MODE_COLOR_OFF_B))

// General config
#define PEDAL_VOLTAGE_PIN           A0
#define RESET_BUTTON_PIN            2
#define MODE_BUTTON_PIN             3
#define HEARTBEAT_LED_PIN           13
#define INDICATOR_LED_PIN           9
#define PWM_LOAD_PIN                5
#define VPWMSETPOINT                2000 
#define VPWMHYSTERESIS              500
#define BROWNOUT_HIGH               1000
#define BROWNOUT_LOW                850


