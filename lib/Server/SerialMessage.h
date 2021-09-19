
/* 
 *  This script describes everything related to the
 *  Serial Message class made on the Arduino side.
 */ 

#include <Arduino.h>
#include <stdint.h>
#include <stdlib.h>
#include <cobs.h>
//OFFSETS
#define BUFSIZE 256
#define COBS 0
#define TASKNUMBER 1
#define ELEVATORNUMBER 2
#define PAYLOAD 3


class SerialMessage //immutable class, should have no setters
{
    private:

            // header attributes: 
            unsigned char* message; // pointer to our packet structure
            uint8_t buffer[BUFSIZE]; // temporary memory allocation
            uint8_t elevatorNum; // indicates what elevator is being requested
            uint8_t taskNum; // indicates the task requested
            uint8_t cobsOverhead; // First cobs byte
            
    public:

            SerialMessage(uint8_t elev, uint8_t task);

            // rx methods:
            void verifyHeader();

            uint8_t storeRxByte();

            // tx methods: 
            void buildHeader(); 
            void checkBuffer(); // check if buffer is full

            //Packet Info getters
            uint8_t getPacketSize();
            uint8_t getElevatorNum();
            uint8_t getTaskNum();
};