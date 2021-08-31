
/* 
 *  This script describes everything related to the
 *  Serial Message class made on the Arduino side.
 */ 

#include <Arduino.h>
#include <stdint.h>
#include <stdlib.h>
#include <cobs.h>


class SerialMessage //immutable class, should have no setters
{
    private: 

            // header attributes: 

            const char* message; //can set the address to null in case of corruption but cant change msg content
            //const unsigned char* buffer[1080]; //treated as a byte
            uint8_t const elevatorNum = 0;
            uint8_t const taskNum = 0;
            //uint8_t const packetSize;
            
    public:

            SerialMessage();

            // rx methods:
            void verifyHeader();

            // tx methods: 
            void buildHeader(); 

            //Packet Info getters
            uint8_t getPacketSize();
            uint8_t getElevatorNum();
            uint8_t getTaskNum();
};