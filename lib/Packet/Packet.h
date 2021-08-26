#include <stdint.h>
//https://bakercp.github.io/PacketSerial/md_GETTING_STARTED.html?

class Packet //immutable class, should have no setters
{
    private: //not using struct as youd need to use pragma pack
        uint8_t const packetSize;
        uint16_t const packetID;
        unsigned char const message;
        int byte;
        //https://stackoverflow.com/questions/5795283/creating-and-sending-data-packets-in-c-c might help?

    public:
        void buildHeader(); //like the constructor?
        void encode(); 
        void transmitData();

        //Packet Info getters
        uint8_t getPacketSize();
        uint16_t getPacketID();

};