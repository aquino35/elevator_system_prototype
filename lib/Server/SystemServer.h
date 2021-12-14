/*
*  This script contains all the methods of the
*  server object used to process anything given by a Client.
*/
#include <Arduino.h>
//#include <cobs.h>

#define BAUDRATE              9600
#define COBS_DELIMETER        0xFF
#define QUEUE_SIZE            255

#define COBS_DECODE_SIZE      14
#define STD_COBS_BUFF_SIZE    13
#define STD_ENCODE_SIZE       14
#define STD_DECODE_SIZE       14

/* Macros for packet structure */
#define EID_OFFSET            0
#define SID_OFFSET            1
#define DOOR_OFFSET           2
#define LIGHT_OFFSET          3
#define FLOOR_OFFSET          4
#define TEMP_OFFSET           5
#define LOAD_OFFSET           6
#define PERSON_OFFSET         7
#define MAINTENANCE_OFFSET    8
#define DIRECTION_OFFSET      9
#define MOVING_OFFSET         10
#define MSG_OFFSET            11


class SystemServer
{
        private:

                uint8_t* queue; // buffer for rx and tx operations.
                size_t byte_counter; 

                /* Variables for elevator attirbutes that will be transmitted always */

                /* header */ 
                uint8_t eid; 
                uint8_t sid;
                /* payload */
                uint8_t door_status;   // elev-> is_door_open()
                uint8_t light_status;  // elev-> is_light_on()
                uint8_t current_floor;  // elev-> get_floor()
                uint8_t temp;        // elev-> get_temp()
                uint8_t load;         // elev-> get_load_weight()
                uint8_t person_counter; // elev-> get_person_count()
                uint8_t maintenance; // elev-> get_person_count()
                uint8_t direction; // elev-> get_person_count()
                uint8_t moving; // elev-> get_person_count()
                uint8_t msg_to_user; // TODO: mapping of msgs on pyserial side

        public: 
                SystemServer();

                void setup(void);
                 
                void loop(void);

                void serial_service_tx(uint8_t* pkt, size_t pkt_size);

                void serial_service_rx(void);

                void exec_service(void);

                void extract_pkt_data(uint8_t* pkt);

                void decode_std_pkt(uint8_t* pkt);

                bool verify_byte(uint8_t data);

                void set_elev_attr(uint8_t* pkt);

                void get_elev_attr(void);

                void set_queue(uint8_t* queue);

                void set_eid(uint8_t eid);

                void set_sid(uint8_t sid);

                void set_door_status(uint8_t door_status);

                void set_light_status(uint8_t light_status);

                void set_floor(uint8_t current_floor);

                void set_temp(uint8_t temp);

                void set_load(uint8_t load);
                               
                void set_person_counter(uint8_t person_counter);

                void set_msg_to_usesr(uint8_t msg_to_user);

                uint8_t get_sid(void);

                uint8_t get_door_status(void);

                uint8_t get_light_status(void);

                uint8_t get_floor(void);

                uint8_t get_temp(void);

                uint8_t get_load(void);

                uint8_t get_person_counter(void);

                uint8_t get_msg_to_user(void);

                uint8_t* get_queue(void);

                size_t cobs_decode(const uint8_t * input, size_t length, uint8_t * output);

                size_t cobs_encode(const uint8_t * input, size_t length, uint8_t * output);

};