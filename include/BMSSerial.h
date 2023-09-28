#ifndef BMSSerial_h
#define BMSSerial_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define SET_SHUNT 2

class BMSSerial
{
private:
    SoftwareSerial p_softSerial;  // Direkt objekt istället för pekare
    long p_serialSpeed;           // BAUD rate for software serial

    byte p_moduleAddress;         // Address of this module
    byte p_sourceAddress;         // Address of sender of the original message
    byte p_destinationAddress;    // Address of recipient of the original message
    byte p_protocolVersion;       // Senders protocol version and version used and max supported in this module
    byte p_version;
    byte p_command;
    byte p_dataSize;
    String p_data;
    bool p_isMaster;              // Boolean to indicate if this is a master or slave

public:
    BMSSerial(int RX, int TX, long BAUD, bool isMaster);  // RX och TX pin för software serial, + Baud rate, + master/slave flag
    void init();                           // Method to initialize or re-initialize the module
    int getModuleAddress();                // Method to get the module address
    void requestAddress();                 // Method to request an address from the master
    void handleAddressAssignment(String message); // Method to handle address assignment message from master
    void assignAddress(byte moduleAddress, byte newAddress); // Method for master to assign address to a module
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
    bool isMaster();  // Method to check if this instance is a master or slave
};

#endif
