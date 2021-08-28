#include <stdint.h>

class SerialMessage //immutable class, should have no setters
{
    private: 
        const char* message; //can set the address to null in case of corruption but cant change msg content
        const unsigned char* buffer; //treated as a byte
        uint16_t const packetID;
        uint8_t const packetSize;
        int byte;
        
    public:

        void buildHeader(); 
        void encode(); 
        void transmitData();

        //Packet Info getters
        uint8_t getPacketSize();
        uint16_t getPacketID();

};