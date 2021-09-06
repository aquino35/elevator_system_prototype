
/* 
 *  This script contains all the methods of the
 *  server object used to process anything given by a Client.
 */ 
#pragma once
#include <SerialMessage.h>
#define BUFSIZE 1024


class Server 
{

private: 

        const unsigned char* msgBuffer[BUFSIZE]; // buffer for msg packet

public:
        // Constructor
        Server(); 

        void begin();
        void run();
        void transmitData(const unsigned char* msgBuffer, uint8_t msg_size); // tx
        void recieveData(); // rx
        void end(); 
};