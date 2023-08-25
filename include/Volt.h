#ifndef Volt_h
#define Volt_h

#include <Arduino.h>

/*
Measuring vcc Voltage by measuring a known voltage with vcc as referense.
*/

class Volt
{
  private:
  int   measuredRefV;                              // how many miliVolt that is expected on the referens pin or internal reference.
  int   refPin;                                    // pin to measure referlece volt. 99 = internal reference
  int   analogIn;                                  // last adC value from volt read.

  public:
  Volt( unsigned int pin, unsigned int refV );    // pin = Arduino pin where ref Voltage is connected.
                                                  // refV = referens voltage on that pin
  long  readVolt(void);                           // Performe a measurement and return vcc volt.
};
# endif