/********************************************************
/****** Pedal Power LED controller Unit *****************
/****** by Matt Little **********************************
/****** Date: 13/9/16 ***********************************
/****** info@re-innovation.co.uk ************************
/****** www.re-innovation.co.uk *************************
/********************************************************

This is the code for an LED controller for pedal power.
It is a universal control program for various functions.

The following items are conencted:

D0 - Rx
D1 - Tx
D2 - SW1 (int)
D3 - SW2 (int)
D4 - SW3
D5 - PWM1
D6 - PWM2
D7 - GPIO
D8 - GPIO
D9 - LED
D10 - SPI - SS
D11 - SPI - MOSI
D12 - SPI - MISO
D13 - SPI - SCLK

A0 - V1 Input voltage
A1 - V2 Input voltage
A2 - Input Grove connectort
A3 - Input Grove conenctor
A4 - I2C SDA
A5 - I2C SCL
A6 - Internal volatge check (100k/10k) to check supply voltage

The program provides the following functions:

It constantly monitors V1. If the voltage > Vpwmlow (= 40V) then the PWM1 is increased.
This happens until the voltage V1 goes lower. Below Vpwmlow then the PWM1 is OFF.
This should have a PID control to control the PWM.

SW3 is used as a digital output to control LED lights (WS2811 type 1-wire).

There are two LED control modes:
Mode 1: Light up challenge

When the voltage V1 is greater than 12V then the lights start to light up.
A Timer is used to switch on the next light until a whole string is lit up.
If the person stops pedalling then the lights are reset to zero.

Mode 2: Energy fill challenge

When voltage V2 (Ultracapacitor) reaches 15V then the lights are set off in a special pattern (TBC).
This will happen until the voltage V2 is <10V.

Button SW1 is a reset button. It sets the LEDs to OFF.

Button SW2 controls which challenge people are doing. Mode 1 or Mode 2.

A voltage divider on the capacitor storage unit gives us the batteryVoltage
If this goes low then want to store the Energy Value into EEPROM so its not lost.
Only want it reset when button pressed.


Written by: Matt Little (matt@re-innovation.co.uk)
Date: 13/9/16
Updated:
PWM control working - needs testing 13/9/16  Matt Little



see www.re-innovation.co.uk for more details

// To DO:


LED control mode 1
LED control mode 2
Check battery voltage
Check switches

PWM control testing on real system
 
*/

/************ External Libraries*****************************/
//We always have to include the library
#include <stdlib.h>
#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/eeprom.h>    // For writing values to EEPROM

#include <Adafruit_NeoPixel.h>


// GPIO
#define SW1 2  // Push switch connected to D2 // This is the RESET
#define SW2 3  // Push switch connected to D3 // This is the MODE CONTROL
#define SW3 4  // Push switch connected to D4
#define PWM1 5  // PWM output connected to D5
#define PWM2 6  // PWM output connected to D6 (used for LED control)
#define LEDOUT 9   // LED on board connected to D7
#define V1 A0  // Voltage input connected to A0 (with 560k/10k)
#define V2 A1  // Voltage connected to A1 (with 150k/10k)
#define VBATT A6  // Battery supply voltage connected to A6 via 100k/10k


#define MAXLEDS 15
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(MAXLEDS, PWM2);
int n = 0;

#define VPWMSETPOINT 2000 // This is the voltage to start PWM at in tens of milli volts
#define VPWMHYSTERESIS 500  // Need the PWM to kick in just below the voltage

int ledMode = 0;  // This is for the two different modes.

// Variables for PI control
long PWM1value = 0;  // Holds the PWM1 value
long proportional = 0;    // The proportional element
long integral = 0;        // The integral element
long error = 0;           // The error signal
float voltageV1;        // Holds the value of the external voltage


float voltageV2;        // Holds the value of the external voltage

/* we always wait a bit between updates of the display */
int delaytime=50;


// ******* Variables *************
// Varibales for writing to EEPROM
int hiByte;      // These are used to store longer variables into EERPRPROM
int loByte;


// Variables for battery voltage check
boolean shutDownFlag = HIGH;   // Stops EEPROM being written to loads of times at low voltage
float batteryVoltage; // Holds the value of the battery voltage

// Variables for Switch checking
// Button debounce


int lastButtonState1 = LOW;   // the previous reading from the input pin
int lastButtonState2 = LOW;   // the previous reading from the input pin
long lastDebounceTime1 = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;  // the last time the output pin was toggled
long debounceDelay = 200;    // the debounce time; increase if the output flickers
boolean button1;  
boolean button2; 
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

boolean checkSW1()
{
  // Here we check each of the switches
  // Needs to be done relatively quickly
  int buttonState1;             // the current reading from the input pin
  int reading = digitalRead(SW1);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState1) {
      buttonState1 = reading;
      if (buttonState1 == LOW) {
        Serial.println("SW1 PRESS");
      }
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState1 = reading;
  return(!buttonState1);
}

boolean checkSW2()
{
  // Here we check each of the switches
  // Needs to be done relatively quickly
  int buttonState2;             // the current reading from the input pin
  int reading = digitalRead(SW2);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState2) {
      buttonState2 = reading;
      if (buttonState2 == LOW) {
        Serial.println("SW2 PRESS");
      }
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState2 = reading;
  return(!buttonState2);
}

void overVoltageControl()
{
  // Our Input is the voltage value. Setpoint is voltSetPoint - adjustable via serial port
  // The output is the FETcontrol PWM freq

  // Read voltage V1:
  voltageV1 = ((analogRead(V1)*3.3*570*100)/(1024*10)); // This gives the analog vbattery voltage
  Serial.print("V1: ");
  Serial.println(voltageV1);  


  // Only need PWM is voltageV1 >VPWMSETPOINT (minus hysteresis)

  if(voltageV1>=VPWMSETPOINT-VPWMHYSTERESIS)
  {
    // Firt calculate the error value
    // This will be in mV and vary up to >1000
    // If the value is 1000 then the voltage is at 14V and the FET should be fully ON
    error = voltageV1 -(VPWMSETPOINT);    
    
    // Calculate the integral value. This will go down when error is negative
    integral = integral + error;
       
    //Proportional gain
    proportional = error;  // This is the PROPORTIONAL GAIN
    
    PWM1value = (proportional + integral)/120;  // This gives us a setpoint
    
     // Need to put some limits on this value:
     if(PWM1value<=0)
     {
       PWM1value = 0;
       integral = 0;
       //proportional =0;  
     }
     if(PWM1value >=255)
     {
       PWM1value = 255;
     }  
  }
  else
  {
    PWM1value = 0;
    error=0;
    integral=0;
  }
  analogWrite(PWM1,PWM1value);  // Sets the PWM value   
  Serial.print("PWM1: ");
  Serial.println(PWM1value);   
}

void setup() {
  
  Serial.begin(115200);    // Set up a serial output for data display and changing parameters
 
  // Set Vref
  analogReference(EXTERNAL);  // Sets the voltage ref to the 3.3V   
  
  pinMode(SW1, INPUT_PULLUP);  // Set the button as an input
  pinMode(SW2, INPUT_PULLUP);  // Set the button as an input
  pinMode(SW3, INPUT_PULLUP);  // Set the button as an input
  pinMode(PWM1, OUTPUT);  // Set the PWM output
  pinMode(PWM2, OUTPUT);  // Set the PWM output
  pinMode(LEDOUT, OUTPUT);  // Set the LED as an output

  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
  
} /*** END OF SETUP****/

void loop() { 

  
  // ****** PWM OVERVOLTAGE CONTROL *****************//
  // Here we implement a basic proportional and Integral Controller
  // This helps smooth the output a bit - need to tune variables
  overVoltageControl();
  // ****** END of PWM OVERVOLTAGE CONTROL **********//


  // ****** CHECK BATTERY VOLTAGE *****************//
  // The battery voltage is checked. If it drops below 4V then we switch off the LEDs and reset
  batteryVoltage = ((analogRead(VBATT)*3.3*110)/(1024*10)); // This gives the analog vbattery voltage
  if(batteryVoltage<4.00)
  {
    Serial.println("LOW VOLTAGE");
    // *** STOP LEDS and shut down everything**** //
    // *** TO DO **** //
  } 
  Serial.print("Batt V: ");
  Serial.println(batteryVoltage);
  // ****** END of CHECK BATTERY VOLTAGE **********//


  // ****** CHECK SWITCHES *****************//
  // This is done using interupts??
  Serial.print("Switch1:");
  button1 = checkSW1();
  Serial.println(button1);
  Serial.print("Switch2:");
  button2 = checkSW2();
  Serial.println(button2);
  // ****** END of CHECK SWITCHES **********//

  // ******* LED CONTROL *******************//
  // Here we control the LEDs depending upon the mode we are in

  // Reset the LEDs is SW1 pressed:
  if(button1==HIGH)
  {
    n=0;  // Reset for mode 1
          // Reset for mode 2

    // Reset the LEDs
    for(int j=0;j<MAXLEDS;j++)
    {
      pixels.setPixelColor(j,0,0,0);

    }
    pixels.show();        
  }

  switch(button2)
  {
    case 0:   // MODE 1 for LEDs
    // In this mode the display will increment until all the LED are lit
    // When all LEDs are lit then we get a 'easter egg' pattern
     if(n<MAXLEDS)
      {   
        for(int j=0;j<=n-1;j++)
        {
          // Colours are RED GREEN BLUE
          // so yellow is 255,255,0
          pixels.setPixelColor(j,255,200,0);
        }
        pixels.setPixelColor(n,255,0,0);
        pixels.show();
        n++;
      }
      else
      {     
        // We have reached the end, so flash the LEDS
        for(int j=0;j<MAXLEDS;j++)
        {
          pixels.setPixelColor(j,255,255, 255);
        }
        pixels.show();
        delay(250);
        for(int j=0;j<MAXLEDS;j++)
        {
          pixels.setPixelColor(j,0,0,0);
        }
        pixels.show();
        delay(250); 
        n=0;  
      }        

    break;
    case 1:   // MODE 2 for LEDs
    // In this mode we wait until the voltage V2 is >15V
    // Then we light up all the LEDs with some pattern until the voltage is <10V
    // Read voltage V2:
    voltageV2 = ((analogRead(V2)*3.3*160*100)/(1024*10)); // This gives the analog vbattery voltage
    Serial.print("V2: ");
    Serial.println(voltageV2);     

    if(voltageV2<1000)
    {
       // Reset the LEDs
      for(int j=0;j<MAXLEDS;j++)
      {
        pixels.setPixelColor(j,0,0,0);
      }
      pixels.show();     
    }
    else if(voltageV2>=1500)
    {

      // NEED TO CHANGE THIS !!!!!!!!!!!*******************************************
      // This is just a test:
      theaterChaseRainbow(50);
      
    }
    break;
  }



  // ******* END of LED CONTROL ***********//  

  // Toggle LED: I'm alive!
  digitalWrite(LEDOUT, !digitalRead(LEDOUT));

  delay(delaytime);
} /*** END OF LOOP ****/

