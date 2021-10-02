#include "SystemServer.h"
 
 
// Global objects
 
SystemServer::pkt_t* rxMsg; // rx signal
SystemServer::pkt_t* txMsg; // tx signal
 
SystemServer::SystemServer(void)
{
 
}
 
void SystemServer::begin(void)
{
   Serial.begin(9600);
   Serial.println("-- Welcome to the Elevator System Prototype! --");
}
 
void SystemServer::run(void)
{
 
}
 
// Transmit to serial channel
void SystemServer::transmit_data(const unsigned char* msg_buffer, uint8_t msg_size)
{
  
   size_t bytesToSend = msg_size;
   size_t encoded_buffer_length = (msg_size) + (msg_size) / 254 + 2;
   uint8_t* encoded_buffer = (uint8_t *) malloc(encoded_buffer_length);
   size_t encodedLength = cobs_encode( msg_buffer, msg_size, encoded_buffer );
 
  
   while(bytesToSend)
   {
       bytesToSend -= Serial.write(encoded_buffer, encodedLength);
 
       if (bytesToSend > msg_size)
       {
           break;
       }
   }
   free(encoded_buffer);
}
 
// Read from serial channel
uint8_t* SystemServer::recieve_data(void)
{
   int cobsByte;
   int nextByte;
   int index = 0;
   uint8_t encodedMsg[256]; /* Stores incoming bytes */
 
   while(Serial.available() > 0)
   {
       cobsByte = Serial.read();   
       nextByte = Serial.read(); //checks the next byte, COBS ends in 00
       while(cobsByte != 0 && nextByte != 0){
           encodedMsg[index] = cobsByte;
           encodedMsg[++index] = nextByte;
       }
 
   }
   return encodedMsg;
}

SystemServer::pkt_t* SystemServer::decode_data(uint8_t* encodedData[]){
    pkt_t* pkt;
    cobs_decode(encodedData[0], 1, &pkt->eid); //Saves the elevatorIdyyyyyyyy
    cobs_decode(encodedData[1], 1, &pkt->sid); //Saves the serviceId
    cobs_decode(encodedData[2], 1, &pkt->aid); //Saves the attributeId
    cobs_decode(encodedData[3], 1, &pkt->payload[DOOR]); //Saves the doorOpen bool
    cobs_decode(encodedData[4], 1, &pkt->payload[LIGHTS]); //Saves the lightsOn bool
    cobs_decode(encodedData[5], 1, &pkt->payload[FLOOR]); //Saves the floor
    cobs_decode(encodedData[6], 1, &pkt->payload[TEMP]); //Saves the temp
    cobs_decode(encodedData[7], 1, &pkt->payload[LOAD]); //Saves the current load
    cobs_decode(encodedData[8], 2, &pkt->payload[WEIGHT]); //Saves weight, uint16 is the next two bytes
    cobs_decode(encodedData[10], 1, &pkt->payload[DIRECTION]); //Saves direction bool, true is up
    cobs_decode(encodedData[11], 1, &pkt->payload[MOVING]); //Savves moving bool
    return pkt;

}
 

void SystemServer::terminate(void)
{
   clear_queue();
   delete elements;
   delete service_handler;
   if(is_queue_empty()){
       Serial.println("SystemServer has been cleared, elevator system service terminated.");
   }
   else{
       Serial.println("SystemServer not cleared correctly, an error has occured.");
   }
  
}
 
void SystemServer::register_service(const char* service_msg, uint8_t sid, void (*cb)(void))
{
   service_handler[service_count] = {service_msg, sid, cb};
 
}

 
 
void SystemServer::verify_header(pkt_t* pkt)
{
   pkt->cobs_overhead = pkt->buffer[COBS_OFFSET]; // Masking attribute with bits to extract
   pkt->sid = pkt->buffer[SERVICEID_OFFSET];
   pkt->eid = pkt->buffer[ELEVATORID_OFFSET];
   pkt->payload = pkt->buffer[PAYLOAD_OFFSET];
}
 
void SystemServer::build_header(pkt_t* pkt)
{
   pkt->buffer[SERVICEID_OFFSET] = pkt->sid; //increase as the next tasknumber
   pkt->buffer[ELEVATORID_OFFSET] = pkt->eid;
   pkt->buffer[PAYLOAD_OFFSET] = pkt->payload;
}

void SystemServer::verify_pkt_buffer(pkt_t* pkt)
{
 
}
 
uint8_t SystemServer::get_pkt_size(pkt_t* pkt)
{
   uint8_t size = 0;
   int i = 0;
   while(pkt->buffer[i] != NULL){ //empty spots in the buffer should be null
       size++;
       i++;
   }   
   return size;
}
 
uint8_t SystemServer::get_eid(pkt_t* pkt)
{
   return pkt->eid;
}
 
uint8_t SystemServer::get_sid(pkt_t* pkt)
{
   return pkt->sid;
}
 
void SystemServer::allocate_pkt(pkt_t* pkt)
{
   pkt = (pkt_t*)malloc(sizeof(pkt_t));
}
 
void SystemServer::deallocate_pkt(pkt_t* pkt)
{
   free(pkt); //memory must be free once again
}
 
void SystemServer::allocate_request(request_t* request)
{
   request = (request_t*)malloc(sizeof(request_t));
}
 
void SystemServer::deallocate_request(request_t* request)
{
   free(request);
}
 
void SystemServer::enqueue(request_t* request)
{
   if (this->is_queue_full())
       Serial.println("Request queue is full!");
   this->elements[this->tail] = request;
   this->tail = (this->tail + 1) % BUFSIZE;
   this->queue_size++;
}
 
 
SystemServer::request_t* SystemServer::dequeue(void)
{
   if(this->is_queue_empty())
       return NULL;
   request_t* result = this->peek_queue();
   this->elements[this->head] = NULL;
   this->head = (this->head + 1) % BUFSIZE;
   this->queue_size--;
   return result;
}
 
uint8_t SystemServer::is_queue_full(void)
{
   return (this->get_queue_size() == BUFSIZE);
}
 
uint8_t SystemServer::is_queue_empty(void)
{
   return this->get_queue_size() == 0;
}
 
void SystemServer::clear_queue(void)
{
   while (this->dequeue() != NULL);
}
 
SystemServer::request_t* SystemServer::peek_queue(void)
{
   if(this->is_queue_empty())
       return NULL;
   return this->elements[this->head];
}
 
int SystemServer::get_queue_size(void)
{
   return this->queue_size;
}