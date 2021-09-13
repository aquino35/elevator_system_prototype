#include "SerialMessage.h"

//Constructor
SerialMessage::SerialMessage()
{
    elevatorNum = 1;
    taskNum = 1;
}

// rx methods:
void SerialMessage::verifyHeader()
{
    cobsOverhead = buffer[COBS]; // Masking attribute with bits to extract
    buffer+TASKNUMBER;
    taskNum = buffer[TASKNUMBER]; // Masking attribute with bits to extract
    buffer+ELEVATORNUMBER;
    elevatorNum = buffer[ELEVATORNUMBER]; // Masking attribute with bits to extract
}
 
// tx methods: 
void SerialMessage::buildHeader()
{

}

//Packet Info getters
uint8_t SerialMessage::getPacketSize()
{

}

uint8_t SerialMessage::getElevatorNum()
{

}

uint8_t SerialMessage::getTaskNum()
{

}
