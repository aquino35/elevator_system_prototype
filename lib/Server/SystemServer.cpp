#include "SystemServer.h"


// Global objects

Server::pkt_t* rxMsg; // rx signal
Server::pkt_t* txMsg; // tx signal 

Server::Server(void)
{

}

void Server::begin(void)
{
    Serial.begin(9600);
    Serial.println("-- Welcome to the Elevator System Prototype! --");
}

void Server::run(void)
{

}

// Transmit to serial channel
void Server::transmit_data(const unsigned char* msg_buffer, uint8_t msg_size)
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
void Server::recieve_data(void)
{
    int byte;

    while( (byte = Serial.read() ) >= 0)
    {
        if ( this->build_rx_task_pkt())
        {
            
        }

    }
}

//Returns true if it terminates correctly
void Server::terminate(void)
{
    clear_queue();
    delete elements;
    delete service_handler;
    if(is_queue_empty()){
        Serial.println("Server has been cleared, elevator system service terminated.");
    }
    else{
        Serial.println("Server not cleared correctly, an error has occured."); 
    }
    
}

void Server::register_service(const char* service_msg, uint8_t sid, void (*cb)(void))
{
    service_handler[service_count] = {service_msg, sid, cb};

}

Server::pkt_t* Server::construct_pkt(void)
{

}



void Server::verify_header(pkt_t* pkt)
{
    pkt->cobs_overhead = pkt->buffer[COBS_OFFSET]; // Masking attribute with bits to extract
    pkt->sid = pkt->buffer[SERVICEID_OFFSET]; 
    pkt->eid = pkt->buffer[ELEVATORID_OFFSET];
}

void Server::build_header(pkt_t* pkt)
{
    cobs_encode(pkt->message, sizeof(pkt->message), pkt->buffer); //encode message with COBS and store those bytes
    pkt->buffer[SERVICEID_OFFSET] = pkt->sid; //increase as the next tasknumber
    pkt->buffer[ELEVATORID_OFFSET] = pkt->eid;
}

void Server::verify_pkt_buffer(pkt_t* pkt)
{

}

uint8_t Server::get_pkt_size(pkt_t* pkt)
{
    uint8_t size = 0;
    int i = 0;
    while(pkt->buffer[i] != NULL){ //empty spots in the buffer should be null
        size++;
        i++;
    }    
    return size;
}

uint8_t Server::get_eid(pkt_t* pkt)
{
    return pkt->eid;
}

uint8_t Server::get_sid(pkt_t* pkt)
{
    return pkt->sid;
}

void Server::allocate_pkt(pkt_t* pkt)
{
    pkt = (pkt_t*)malloc(sizeof(pkt_t));
}

void Server::deallocate_pkt(pkt_t* pkt)
{
    free(pkt); //memory must be free once again
}

void Server::allocate_request(request_t* request)
{
    request = (request_t*)malloc(sizeof(request_t));
}

void Server::deallocate_request(request_t* request)
{
    free(request); 
}

void Server::enqueue(request_t* request)
{
    if (this->is_queue_full())
        Serial.println("Request queue is full!");
    this->elements[this->tail] = request;
    this->tail = (this->tail + 1) % BUFSIZE; 
    this->queue_size++;
}


Server::request_t* Server::dequeue(void)
{
    if(this->is_queue_empty())
        return NULL;
    request_t* result = this->peek_queue();
    this->elements[this->head] = NULL;
    this->head = (this->head + 1) % BUFSIZE;
    this->queue_size--;
    return result;
}

uint8_t Server::is_queue_full(void)
{
    return (this->get_queue_size() == BUFSIZE);
}

uint8_t Server::is_queue_empty(void)
{
    return this->get_queue_size() == 0;
}

void Server::clear_queue(void)
{
    while (this->dequeue() != NULL);
}

Server::request_t* Server::peek_queue(void)
{
    if(this->is_queue_empty())
        return NULL;
    return this->elements[this->head];
}

int Server::get_queue_size(void)
{
    return this->queue_size;
}
