 
/*
*  This script contains all the methods of the
*  server object used to process anything given by a Client.
*/
#pragma once
#include <Arduino.h>
#include <stdlib.h>
#include<Elevator.h>
#include <cobs.h>
/* MACROS */
#define ELEVATOR_COUNT   2      /* amount of elevators present in server*/
#define SERVICES        15      /* amount of services available in Server */
#define BUFSIZE         256
/* OFFSETS */
#define COBS_OFFSET           0
#define SERVICEID_OFFSET      1
#define ELEVATORID_OFFSET     2
#define PAYLOAD_OFFSET        3
/* PAYLOAD MACROS */
#define PAYLOAD_SIZE     8
#define DOOR             0
#define LIGHTS           1
#define FLOOR            2
#define TEMP             3
#define LOAD             4
#define WEIGHT           5
#define DIRECTION        6
#define MOVING           7
 
 


class SystemServer
{
       public:
       /*
       The following serial packet (or message) structure is
       defined to meet the UART protocol and communicate with the Client.
       */
       typedef struct packet
       {
               uint8_t buffer[BUFSIZE]; /* temporary memory allocation */
               uint8_t eid; /* indicates what elevator is being requested */
               uint8_t sid; /* indicates what service is being requested  */
               uint8_t aid; /* Indicates what attribute we're referring to */
               uint8_t cobs_overhead; /* First cobs encode byte*/
               uint8_t payload[PAYLOAD_SIZE]; /* Contains specific information about the elevator */
       }pkt_t;
 
       /*
       We use this next structure "request" to define more
       clearly what it is the client is asking to perfom.
       */
       typedef struct request
       {
               uint8_t eid; /* indicates what elevator is being requested */
               uint8_t sid; /* indicates what service is being requested  */
       }request_t;
      
 
       /*
       Contains specific information about the elevator such as
       what floor the elevator is on, the elevator num, and so on.
       */
 
 
       SystemServer(void); /* Constructor */
 
       /* Queue attributes */
       int head=-1, tail=-1, queue_size=0;
       request_t* elements[BUFSIZE]; /* container for holding requests*/
 
       /* Array of function pointer that will create a table to handle all our services. */
       int service_count = 0;
       void(*service_handler[SERVICES])(const char* service_msg, uint8_t service_num, void (*cb)(void));
 
       //const unsigned char* msg_buffer[BUFSIZE]; // buffer for msg packet
 
       /* Server Methods */
       void begin(void);
       void run(void);
       void transmit_data(const unsigned char* msgBuffer, uint8_t msg_size); /* tx */
       uint8_t* recieve_data(void); /* rx */
       pkt_t* decode_data(uint8_t* encodedData[]); /* Decodes recieved packet */
       void terminate(pkt_t* pkt); /* end server life */
       void register_service(const char* service_msg, uint8_t service_num, void (*cb)(void)); /* function is still incompleate */
 
       /* Packet Methods */
       void verify_header(pkt_t* pkt); /* rx */
       void build_header(pkt_t* pkt); /* rx */
       void verify_pkt_buffer(pkt_t* pkt);/* check if buffer is full */
       uint8_t get_pkt_size(pkt_t* pkt); /* get size of pkt */
       uint8_t get_eid(pkt_t* pkt); /* returns elevator id from pkt */
       uint8_t get_sid(pkt_t* pkt); /* returns service id from pkt */
       uint8_t get_aid(pkt_t* pkt);
       uint8_t* get_payload(pkt_t* pkt);
       void allocate_pkt(pkt_t* pkt); /* allocate structure in memory */
       void deallocate_pkt(pkt_t* pkt); /* deallocate structure in memory */
      
 
       /* Request Methods */
       void allocate_request(request_t* request); /* allocate structure in memory */
       void deallocate_request(request_t* request); /* deallocate structure in memory */
 
       /* Queue Methods */
       void enqueue(request_t* request); /* adds request to queue */
       request_t* dequeue(void); /* removes request from queue */
       uint8_t is_queue_full(void); /* verifies if queue is full */
       uint8_t is_queue_empty(void); /* verifies if queue is empty */
       void clear_queue(void); /* clears queue */
       request_t* peek_queue(void); /* gets the value of the front of the queue */
       int get_queue_size(void); /* return current size of queue */
};


