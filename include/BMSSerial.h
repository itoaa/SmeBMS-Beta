#ifndef BMSSerial_h
#define BMSSerial_h

#include <Arduino.h>
#include <string.h>
#include "setup.h"
#include <SoftwareSerial.h>

/*
 Konstruktor av BMSSerial. ex (BMSSerial .....

  Ver   1.0
      First implementation. for testing in Beta 1, can be major canges witout revision 
*/

#define SET_SHUNT 2

class BMSSerial
{
  private:
    SoftwareSerial p_softSerial;
    long    p_serialSpeed;                                          // BAUD rate on software serial

// This is not needed i gues. Only one to send to.
    // int     p_senderAddress, p_reciverAddress;                      // Addresses of sending and resinving in the local transmission.

    int     p_sourceAddress;
    int     p_destinationAddress;                  // Address of sender of the original message, and who it is sent to.
    int     p_protocolVersion;                                                // Senders protocol version and version used and max supported in this module
    int     p_version;
    int     p_command;
    int     p_dataSize;
    String  p_data;


  public:
    BMSSerial();                      
    BMSSerial(int RX,int TX,long BAUD);          // RX and TX pin for software serial, + Baud tare
    int SleapWhaitForData();
    char getMessage(void);
    int sendMessage();
    int setDest(char dAddress);
    int setSource(char sAddress);
    int setVersion(char pVersion);
    int setCommand(char Command);
    int setData(int Data);
    boolean dataRecived(void);
    char processSerial();
    
  };
# endif