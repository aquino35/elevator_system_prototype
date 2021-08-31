#include "SystemServer.h"

SerialMessage* rxMsg = new SerialMessage(); // rx signal
SerialMessage* txMsg = new SerialMessage(); // tx signal 


Server::Server()
{
    begin();
}

void Server::begin()
{
    Serial.begin(9600);
    Serial.println("-- Welcome to the Elevator System Prototype! --");
}

void Server::run()
{
}


void Server::transmitData(unsigned char* msgBuffer, uint8_t msgSize)
{
    
    size_t bytesToSend = msgSize;
    size_t encoded_buffer_length = (msgSize) + (msgSize) / 254 + 2; 
    uint8_t *encoded_buffer = (uint8_t *) malloc(encoded_buffer_length); 
    size_t encodedMsg = cobs_encode( msgBuffer, msgSize, encoded_buffer );

    
    while(bytesToSend)
    {
        bytesToSend -= Serial.write(msgBuffer, msgSize);

        if (bytesToSend > msgSize)
        {
            break;
        }
    }

}

void Server::recieveData()
{
    int byte;
}
