#include <stdint.h>

class SerialMessage //immutable class, should have no setters
{
    private: 
        uint8_t const packetSize;
        uint16_t const packetID;
        const unsigned char* message; //can set the address to null in case of corruption but cant change msg content
        int byte;
        const unsigned char* buffer; //treated as a byte
        
    public:
        void buildHeader(); 
        void encode(); 
        void transmitData();

        //Packet Info getters
        uint8_t getPacketSize();
        uint16_t getPacketID();

};