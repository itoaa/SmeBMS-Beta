//
//    Programerare:   Ola Andersson
//    Version:        0.1
//    Beskrivning:    Ett första försök till att få SmeBMS att komunisera via en seriell loop
//                    Använder SoftSerial.
//                    Sleep mode implemented.
//                    Implementerar bara commando V, S E och D

#include "setup.h"
#include "Volt.h"
#include <avr/sleep.h>
#include "BMSSerial.h"

BMSSerial bmsSerial(RX_PIN,TX_PIN,BAUDRATE, SLAVE);

Volt myVolt(ANALOG_REF_PIN,1200);

#include <Arduino.h>

void setup() 
{
  pinMode(PWM_PIN, OUTPUT);   // sets the pin as output

  // Sätt upp sleep-mode för låg strömförbrukning
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // Aktivera PB4 (RX) som external interrupt
  GIMSK |= (1 << PCIE); // Pin Change Interrupt Enable
  PCMSK |= (1 << PCINT4); // Pin Change Mask

}

long sv,nsv;

void loop() 
{
 // PSerial.SleapWhaitForData();

  sleep_enable(); // Återgå till sleep-mode för att spara ström
  

  delay(500);
  nsv = myVolt.readVolt();
  delay(500);

  analogWrite(PWM_PIN,100);
  
  delay(10);
  sv = myVolt.readVolt();
  delay(10);
  analogWrite(PWM_PIN,0);

 
  sleep_mode();

}
