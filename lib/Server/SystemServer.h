
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


class Server 
{
        public:
        /* 
        The following serial packet (or message) structure is 
        defined to meet the UART protocol and communicate with the Client.
        */
        typedef struct packet
        {
                unsigned char* message; /* pointer to pkt struct */
                uint8_t buffer[BUFSIZE]; /* temporary memory allocation */
                uint8_t eid; /* indicates what elevator is being requested */
                uint8_t sid; /* indicates what service is being requested  */
                uint8_t cobs_overhead; /* First cobs encode byte*/
                payload_t payload;
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
        typedef struct payload
        {
                uint8_t door_status;
                uint8_t lights; 
                uint8_t floor;
                uint8_t temp;
                uint8_t capacity; 
                uint16_t load_weight; 
                uint8_t direction /* 1 for up, 0 for down. Making it a bool would be confusing as one could interpret the elevator is stuck */
                bool canMove; /* Whether the elevator can move, for example, it can't in emergency and maintance states */
                
        }payload_t;


        Server(void); /* Constructor */

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
        void recieve_data(void); /* rx */
        void terminate(void); /* end server life */
        void register_service(const char* service_msg, uint8_t service_num, void (*cb)(void)); /* function is still incompleate */

        /* Packet Methods */
        pkt_t* construct_pkt(void); /* packet constructor */
        void verify_header(pkt_t* pkt); /* rx */
        void build_header(pkt_t* pkt); /* rx */
        void verify_pkt_buffer(pkt_t* pkt);/* check if buffer is full */
        uint8_t get_pkt_size(pkt_t* pkt); /* get size of pkt */
        uint8_t get_eid(pkt_t* pkt); /* returns elevator id from pkt */ 
        uint8_t get_sid(pkt_t* pkt); /* returns service id from pkt */ 
        void allocate_pkt(pkt_t* pkt); /* allocate structure in memory */
        void deallocate_pkt(pkt_t* pkt); /* deallocate structure in memory */
        

        /* Request Methods */
        void allocate_request(request_t* request); /* allocate structure in memory */
        void deallocate_request(request_t* request); /* deallocate structure in memory */
        uint8_t build_rx_task_pkt(int byte);

        /* Queue Methods */
        void enqueue(request_t* request); /* adds request to queue */
        request_t* dequeue(void); /* removes request from queue */
        uint8_t is_queue_full(void); /* verifies if queue is full */
        uint8_t is_queue_empty(void); /* verifies if queue is empty */ 
        void clear_queue(void); /* clears queue */ 
        request_t* peek_queue(void); /* gets the value of the front of the queue */
        int get_queue_size(void); /* return current size of queue */ 
};