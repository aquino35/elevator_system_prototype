#include <stdint.h>

class SerialMessage //immutable class, should have no setters
{
    private: 
        uint8_t const packetSize;
        uint16_t const packetID;
        const unsigned char* message; //https://stackoverflow.com/questions/21476869/constant-pointer-vs-pointer-to-constant
        int byte;
        uint16_t* buffer;
        
    public:
        void buildHeader(); 
        void encode(); 
        void transmitData();

        //Packet Info getters
        uint8_t getPacketSize();
        uint16_t getPacketID();

};