#include "VCCMeasure.h"

// Konstruktor av VCCMeasure. ex (VCCMeasure(2,PB2). sätter pin PB2 som mätpinner för referens spänning. Första parametern: 1 = internal 1.1v ref, 2 = extrern ref
//
//  Ver   1.0
//      First implementation. Only internal 1.1v icluded
//
VCCMeasure::VCCMeasure(int mode, int pin, int vRef)
{
  if (mode == 1)  // Internal 1,1v ref
  {
      // Read 1.1V reference against AVcc
      // set the reference to Vcc and the measurement to the internal 1.1V reference
      #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
          ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
      #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
          ADMUX = _BV(MUX5) | _BV(MUX0);
      #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
          ADMUX = _BV(MUX3) | _BV(MUX2);
      #else
          ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
      #endif  

      delay(2); // Wait for Vref to settle
  }

  if (mode == 2)  // External ref
  {
    analogIn = pin;
    pinMode(pin, INPUT);
  }
}

// Subrutine to measure a referense volt and calculate the VCC
long VCCMeasure::readVolt(void)
{
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA,ADSC)); // measuring

    uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
    uint8_t high = ADCH; // unlocks both

    long result = (high<<8) | low;

    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000    
                         
    return result;
}