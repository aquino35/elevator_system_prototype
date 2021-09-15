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
    taskNum = buffer[TASKNUMBER]; // Masking attribute with bits to extract
    elevatorNum = buffer[ELEVATORNUMBER]; // Masking attribute with bits to extract
}

uint8_t SerialMessage::storeRxByte()
{

}
 
// tx methods: 
void SerialMessage::buildHeader() //setting parts of the buffer to elements in the message?
{

}

void SerialMessage::checkBuffer() //how is this different from verify header?
{

}

//Packet Info getters
uint8_t SerialMessage::getPacketSize()
{
    uint8_t size = 0;
    int i = 0;
    while(buffer[i] != NULL){ //empty spots in the buffer should be null
        size++;
        i++;
    }    
    return size;
}

uint8_t SerialMessage::getElevatorNum()
{
    return elevatorNum;
}

uint8_t SerialMessage::getTaskNum()
{
    return taskNum;
}
