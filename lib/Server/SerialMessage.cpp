#include "SerialMessage.h"

//Constructor
SerialMessage::SerialMessage()
{
    isCorrupted = 0; 
    elevatorNum = 1;
    taskNum = 1;
}

// rx methods:
void SerialMessage::verifyHeader(unsigned x)
{
    if(isCorrupted == 0)
    {
        message++;
        taskNum = x & 0x1; // Masking attribute with bits to extract
        x>>1; // shift 
        elevatorNum = x & 0x1; // Masking attribute with bits to extract
        x>>1; // shift 

        if (getPacketSize()>sizeof(buffer))
        {
            isCorrupted = 1;
        }
    }
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
