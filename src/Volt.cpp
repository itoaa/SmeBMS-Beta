#include "Volt.h"

// Konstruktor av VOLT. ex (VOLT(PB2,1500). sätter pin PB2 som mätpinner för referens spänning.
Volt::Volt(unsigned int pin, unsigned int refV)
{
  pinMode(pin, INPUT);
  refPin = pin;
  measuredRefV = refV;
}

// Subrutine to measure inputvoltagePin (multiple times for normalization)
long Volt::readVolt(void)
{
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  //#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
   // ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  //#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  //  ADMUX = _BV(MUX5) | _BV(MUX0);
  //#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  //  ADMUX = _BV(MUX3) | _BV(MUX2);    // Vgb? internal?
  #if (refPin == PB2)  
    ADMUX = _BV(MUX0);                // ADC1, external ref.
  #elif (refPin == 0)
    ADMUX = _BV(MUX3) | _BV(MUX2);    // internal 1.1V ref
  #else
  // Not supported
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

 //  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000    
  result = 1227600L / result; // Calculate Vcc (in mV); 1125300 = 1.2*1023*1000    
                         
  return result;
  }