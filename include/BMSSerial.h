#ifndef BMSSerial_h
#define BMSSerial_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define SET_SHUNT 2

class BMSSerial
{
private:
    SoftwareSerial p_softSerial;  // Direkt objekt istället för pekare
    long p_serialSpeed;           // BAUD rate for software serial

    byte p_sourceAddress;
    byte p_destinationAddress;    // Address of sender of the original message, and who it is sent to.
    byte p_protocolVersion;       // Senders protocol version and version used and max supported in this module
    byte p_version;
    byte p_command;
    byte p_dataSize;
    String p_data;

public:
    BMSSerial(int RX, int TX, long BAUD);  // RX och TX pin för software serial, + Baud rate
    int sleepWaitForData();
    char getMessage(void);
    int sendMessage();
    int setDest(byte dAddress);
    int setSource(byte sAddress);
    int setVersion(byte pVersion);
    int setCommand(byte Command);
    int setData(const String& Data);  // Förändrad för att acceptera en sträng
    bool dataReceived(void);
    char processSerial();
};

#endif
