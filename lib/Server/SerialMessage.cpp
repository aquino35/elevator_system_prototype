#include "SerialMessage.h"

//Constructor
SerialMessage::SerialMessage()
{
    isCorrupted = 0; 
    elevatorNum = 1;
    taskNum = 1;
}

// rx methods:
void SerialMessage::verifyHeader(unsigned bitOffset)
{
    if(isCorrupted == 0){
        message++;
        getTaskNum(message);
        bitOffset>>1;
        getElevatorNum(message);
        bitOffset>>1;
        if (getPacketSize()>sizeof(buffer)){
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

uint8_t SerialMessage::getElevatorNum(unsigned bitOffset)
{
    elevatorNum = bitOffset;
    message++;
}

uint8_t SerialMessage::getTaskNum(unsigned bitOffset)
{
    taskNum = bitOffset;
    message++;
}
