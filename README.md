# Pedal Powered Fairy Lights

## Pre-requisites

* Install the Arduino IDE 1.6.6 or later
** Windows & Mac users may find a download link here: https://www.arduino.cc/en/Main/Software
** Major Linux distros carry it in their software repositories, or the link above may be used
* Install the Adafruit_NeoPixel.h library: https://github.com/adafruit/Adafruit_NeoPixel

## Building Using the Arduino IDE

This method is preferred on Windows and for casual users who just want to build and use the project.

* Open Arduino IDE 
* Open pedal_powered_fairy_lights/pedal_powered_fairy_lights.ino
* Set the board to "Arduino Nano" (under the Tools -> Board menu)
* Connect Nano 
* Click the Upload button on the tool bar

## Using make on Linux

This alternative build system may also be used. It is an alternative to using the Arduino IDE and may be preferred by some users. 

* Intall the Arduino-Makefile system: https://github.com/sudar/Arduino-Makefile
* Edit the arduino_inc.mk file and set the include line to point at where you installed Arduino-Makefile
* In a shell, from the pedal_powered_fairy_lights directory, use the command "make upload" to build and install the code

## LED 'flare' ideas

* Random static burst
* Plasma
* Block bounce
* Pour fill
* Lightning

## Known Issues

Because the Arduino IDE won't handle including a library from another library (version < 1.6.6), you must use v 1.6.6 or later.
