
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

            unsigned char* message; // pointer to our packet structure
            const unsigned char* buffer[1080]; // temporary memory allocation
            uint8_t elevatorNum; // indicates what elevator is being requested
            uint8_t taskNum; // indicates the task requested
            uint8_t isCorrupted; // indicates if the message is corrupted.
            //uint8_t const packetSize;
            
    public:

            SerialMessage();

            // rx methods:
            void verifyHeader(unsigned bitOffset);

            // tx methods: 
            void buildHeader(); 

            void checkBuffer(); // check if buffer is full

            //Packet Info getters
            uint8_t getPacketSize();
            uint8_t getElevatorNum(unsigned bitOffset);
            uint8_t getTaskNum(unsigned bitOffset);
};