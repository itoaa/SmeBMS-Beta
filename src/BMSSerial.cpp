#include "BMSSerial.h"

// Konstruktor av VCCMeasure. ex (VCCMeasure(2,PB2). sätter pin PB2 som mätpinner för referens spänning. Första parametern: 1 = internal 1.1v ref, 2 = extrern ref
//
//  Ver   1.0
//      First implementation. Only internal 1.1v icluded
//

/*
BMSSerial::BMSSerial()          // RX and TX pin for software serial, and BAUD-rate
{
    pSerialSpeed = BaudRate;
    
    softSerial_ = SoftwareSerial(RXPin,TXPin);

}
*/

BMSSerial::BMSSerial(int RX, int TX, long BAUD)  : p_softSerial(RX,TX)
 // RX and TX pin for software serial, and BAUD-rate
{
    p_serialSpeed = BAUD;

     // Define pin modes for TX and RX
    pinMode(RX, INPUT);
    pinMode(TX, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
    p_softSerial.begin(p_serialSpeed);   
    
}





int BMSSerial::sleepWaitForData()
{
    return 0;
}
int BMSSerial::sendMessage()
{
  p_softSerial.print('#');
  p_softSerial.print(p_sourceAddress);
  p_softSerial.print(p_destinationAddress);
  p_softSerial.print(p_protocolVersion);
  p_softSerial.print(p_command);
  p_softSerial.print('4');               // Send 4 bytes
  p_softSerial.println(p_data);
    return 0;
}
int BMSSerial::setDest(byte dAddress)
{
    p_destinationAddress = dAddress;
    return 0;
}
int BMSSerial::setSource(byte sAddress)
{
    p_sourceAddress= sAddress; 
    return 0;
}
int BMSSerial::setVersion(byte pVersion)
{
    p_protocolVersion= pVersion;
    return 0;
}
int BMSSerial::setCommand(byte Command)
{
    p_command = Command;
    return 0;
}
int BMSSerial::setData(const String& Data)
{
    p_data = Data;
    return 0;
}
bool BMSSerial::dataReceived(void)
{
  if (p_softSerial.available())
      {
          return 1;
      }
      return 0;
}

char BMSSerial::processSerial()
{
  char sb;
  String inString;
  sb = p_softSerial.read();
  if (sb == '#')                              // If start of transmission
  {
    p_sourceAddress = p_softSerial.read();                   // Source address
    p_destinationAddress= p_softSerial.read();                   // Destination address
    p_protocolVersion= p_softSerial.read();                   // Protokol Version
    p_command= p_softSerial.read();                   // Command
    p_dataSize= p_softSerial.read();                   // Size of chars to come
    for (int i = 1; i< p_dataSize; i++)
    {
      int inChar = p_softSerial.read();
      if (isDigit(inChar))
      {
        inString += (char)inChar;
      }
    }
    inString += '\n';
    p_data= inString.toInt();                  

//    serial.println("Got a command");
    
    if (p_destinationAddress == 'A')               // Is the message to me (addr A) ??
    {                                   // Command sent to me, return Command for processing
        return(p_command);
    }

    if (p_destinationAddress == 'Z' )              // Is the message a broadcast (addr Z) ?? 
    {                                   
        sendMessage();                  // Send package unchanged to next module and process data
        return 0;
    }

    if (p_destinationAddress == 'X')               // Is the message sent to master (addr X) ?? 
    {                                   // inclese Source addres by 1 and send it to next module.
        p_sourceAddress ++ ;               // inclese Source addres by 1  
        sendMessage();
        return 0;
    }

    if (p_sourceAddress == 'X')             // Is the message sent from master (addr X) ?? 
    {                                   // inclese Dest addres by 1 and send it to next module.
        p_destinationAddress ++;      // inclese Dest addres by 1  
        sendMessage();
        return 0;
    }
  } // if #
return 0;
}