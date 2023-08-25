#ifndef VCCMeasure_h
#define VCCMeasure_h

#include <Arduino.h>
/*
 Konstruktor av VCCMeasure. ex (VCCMeasure(2,PB2). sätter pin PB2 som mätpinner för referens spänning. Första parametern: 1 = internal 1.1v ref, 2 = extrern ref

  Ver   1.0
      First implementation. Only internal 1.1v icluded
*/

class VCCMeasure
{
  private:
  int   measuredRefV;                              // how many miliVolt that is expected on the referens pin or internal reference.
  int   refPin;                                    // pin to measure referlece volt. 99 = internal reference
  int   analogIn;                                  // last adC value from volt read.

  public:
  VCCMeasure(int mode, int pin, int refV);        // pin = Arduino pin where ref Voltage is connected. Mode is implemented later
                                                  // refV = referens voltage on that pin in mV
  long  readVolt(void);                           // Performe a measurement and return vcc volt.
};
# endif