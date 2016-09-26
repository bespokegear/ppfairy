#include "VoltMode.h"
#include "Util.h"
#include <Arduino.h>
#include <EEPROM.h>

VoltMode::VoltMode() :
    DisplayMode()
{
#ifdef DEBUG
    Serial.println(F("VoltMode::VoltMode()"));
#endif
    // get _lastPixel from EEPROM
    restoreFromEEPROM();
}

void VoltMode::start()
{
#ifdef DEBUG
    Serial.println(F("VoltMode start"));
#endif
    // fetch _lastPixel value from EEPROM
    _lastPixel = 0;
    _timeLeft = VOLT_MODE_TIME;
    DisplayMode::start();
    writePixels();
}

void VoltMode::stop()
{
#ifdef DEBUG
    Serial.print(F("VoltMode stop"));
#endif
    _lastPixel = 0;
    DisplayMode::stop();
}

void VoltMode::modeUpdate()
{
    uint16_t vIn = highVoltageConversion(PEDAL_VOLTAGE_PIN);
#ifdef DEBUGVIN
    Serial.print(F("vIn="));
    Serial.print(vIn);
#endif
    if (vIn < VOLT_MODE_VMIN) {
        vIn = VOLT_MODE_VMIN;
    } else if (vIn > VOLT_MODE_VMAX) {
        vIn = VOLT_MODE_VMAX;
    }
#ifdef DEBUGVIN
    Serial.print(F(", clipped="));
    Serial.print(vIn);
#endif
    vIn -= VOLT_MODE_VMIN;
#ifdef DEBUGVIN
    Serial.print(F(", adjust="));
    Serial.println(vIn);
#endif

    if (_timeLeft > vIn) {
        _timeLeft -= vIn;
    } else if (_lastPixel < _pixels.numPixels()) {
#ifdef DEBUG
    Serial.println(F("+pixel"));
#endif
        _lastPixel++;
        writePixels();
        _timeLeft = VOLT_MODE_TIME;
    }
    
    return true;
}

void VoltMode::enterBrownout()
{
#ifdef DEBUG
    Serial.println(F("VoltMode::enterBrownout"));
#endif
    _pixels.clear();
    _pixels.show();
    // saves _lastPixel;
    saveToEEPROM(); 
}

void VoltMode::exitBrownout()
{
#ifdef DEBUG
    Serial.println(F("VoltMode::exitBrownout"));
#endif
    // restore _lastPixel
    restoreFromEEPROM(); 
    // restore pixels on LED strip
    writePixels();
}

void VoltMode::saveToEEPROM()
{
#ifdef DEBUG
    Serial.print(F("VoltMode::saveToEEPROM <- "));
    Serial.println(_lastPixel);
#endif
    uint16_t lp = _lastPixel;
    uint8_t* ptr = (uint8_t*)(&lp);
    EEPROM.write(VOLT_MODE_EEPROM_OFFSET+0, ptr[0]);
    EEPROM.write(VOLT_MODE_EEPROM_OFFSET+1, ptr[1]);
}

void VoltMode::restoreFromEEPROM()
{
    uint16_t lp;
    uint8_t* ptr = (uint8_t*)(&lp);
    ptr[0] = EEPROM.read(0);
    ptr[1] = EEPROM.read(1);
    _lastPixel = lp;
#ifdef DEBUG
    Serial.print(F("VoltMode::restoreFromEEPROM -> "));
    Serial.println(_lastPixel);
#endif
}

void VoltMode::writePixels()
{
#ifdef DEBUG
    Serial.println(F("VoltMode::writePixels"));
#endif
    for (uint16_t i=0; i<_pixels.numPixels(); i++) {
        if (i < _lastPixel) {
            _pixels.setPixelColor(i, VOLT_MODE_COLOR_ON);
        } else {
            _pixels.setPixelColor(i, VOLT_MODE_COLOR_OFF);
        }
    }
    _pixels.show();
}
