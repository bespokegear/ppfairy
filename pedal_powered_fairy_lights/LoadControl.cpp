#include "Config.h"
#include "LoadControl.h"
#include "PedalVoltage.h"
#include <Arduino.h>

LoadControl::LoadControl() :
    PWM1value(0),
    proportional(0),
    integral(0),
    error(0),
    last(0)
{
    pinMode(PWM_LOAD_PIN, OUTPUT);
    // Make sure the load is OFF to start with
    digitalWrite(PWM_LOAD_PIN, LOW);
}

void LoadControl::modeUpdate()
{
    if (millis() < last + LOAD_CONTROL_PERIOD_MS) {
        return;
    }
    last = millis();
    voltageV1 = PedalVoltage.get();
    if (voltageV1 >= VPWMSETPOINT - VPWMHYSTERESIS) {
        // in mV and vary up to >1000
        // if the value is 1000 then the voltage is at 14V and the FET should be fully ON
        error = voltageV1 - VPWMSETPOINT;
        // integral value will go down when error is negative
        integral = integral + error;
        // proportional gain
        proportional = error;
        // this gives us a setpoint
        PWM1value = (proportional + integral) / 120;

        // apply limits
        if (PWM1value <= 0) {
            PWM1value = 0;
            integral = 0;
        }
        if (PWM1value >= 255) {
            PWM1value = 255;
        }
    } else {
        PWM1value = 0;
        error = 0;
        integral = 0;
    }
#ifndef NO_LOAD_CONTROL
    // Set the PWM value 
    analogWrite(PWM_LOAD_PIN, PWM1value);
#endif

#ifdef DEBUGLOAD
#ifndef NO_LOAD_CONTROL
    Serial.print(F("PWM="));
#else
    Serial.print(F("PWM (dis)="));
#endif
    Serial.println(PWM1value);
#endif
}

