#include "SerialMessage.h"

//Constructor
SerialMessage::SerialMessage(uint8_t elev, uint8_t task) //use these as inputs to initialize the message
{
    elevatorNum = elev;
    taskNum = task;
}

// rx methods:
void SerialMessage::verifyHeader()
{
    cobsOverhead = buffer[COBS]; // Masking attribute with bits to extract
    taskNum = buffer[TASKNUMBER]; 
    elevatorNum = buffer[ELEVATORNUMBER]; 
}

uint8_t SerialMessage::storeRxByte()
{

}
 
// tx methods: 
void SerialMessage::buildHeader() //setting parts of the buffer to elements in the message?
{
    cobs_encode(message, sizeof(message), buffer[COBS]); //encode message with COBS and store those bytes
    buffer[TASKNUMBER] = taskNum; //increase as the next tasknumber
    buffer[ELEVATORNUMBER] = elevatorNum;
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
