#include <SystemServer.h>


SystemServer::SystemServer()
{
  this->byte_counter = 0;
  this->eid = 0;
  this->door_status = 0;    
  this->light_status = 0;   
  this->current_floor = 0;  
  this->pid = 0;
  this->temp = 0;          
  this->load = 0;           
  this->person_counter = 0; 
  this->maintenance = 0;    
  this->direction = 0;      
  this->moving = 0;         
  this->msg_to_user = 0; 
  this->queue = (uint8_t*) malloc(sizeof(uint8_t) * QUEUE_SIZE);
}


void SystemServer::setup(void) 
{
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  delay(0.5); // avoids any nonetypes in transmission
}


void SystemServer::loop(void) 
{
  // put your main code here, to run repeatedly:
  serial_service_tx(this->queue, STD_ENCODE_SIZE);
  delay(0.5);
  serial_service_rx();
}


void SystemServer::serial_service_tx(uint8_t* pkt, size_t pkt_size)
{
    /* Standard packet for transmission */
    static uint8_t std_pkt[STD_COBS_BUFF_SIZE] = {this->eid, this->door_status, this->light_status, this->current_floor, this->pid, this->temp, 
                                                  this->load, this->person_counter, this->maintenance, this->direction, this->moving, 
                                                  this->msg_to_user,  COBS_DELIMETER};
    
    this->byte_counter = cobs_encode(std_pkt, pkt_size, pkt);
    size_t bytes_to_send = pkt_size;

    while (bytes_to_send)
    {
        bytes_to_send -= Serial.write(&pkt[pkt_size - bytes_to_send], bytes_to_send);
        Serial.flush();
        free(this->queue);
        this->byte_counter = 0;

        // Arithmetic overflow due to sending more bytes than expected
        if (bytes_to_send > pkt_size)
        {
            break;
        }

    }
}


void SystemServer::serial_service_rx(void)
{
    uint8_t recieved_byte;

    while ((recieved_byte = Serial.read())>=0) 
    {
            if(verify_byte(recieved_byte))
            {
                decode_std_pkt(this->queue);
                //serial_service_tx(this->queue,STD_ENCODE_SIZE); //tentative could change when connected to elev
            }
    }
}


bool SystemServer::verify_byte(uint8_t data)
{
    if (!data)
    {
        return true;
    }

    if (this->byte_counter < QUEUE_SIZE) 
    {
      queue[this->byte_counter++] = data; 
    }
    else 
    {
        this->queue[0] = data;
        this->byte_counter = 1;
    }
    return false;
}


void SystemServer::decode_std_pkt(uint8_t* pkt) 
{
    static uint8_t encoded_buffer[STD_DECODE_SIZE];
    memcpy(encoded_buffer, pkt, byte_counter);  // Pass encoded pkt to inner pkt

    this->byte_counter = cobs_decode(encoded_buffer, byte_counter, pkt);
    extract_pkt_data(pkt);
}


void SystemServer::extract_pkt_data(uint8_t* pkt)
{
    /* Extracts standard pkt data */
    
    this->eid =  pkt[EID_OFFSET];
    this->door_status =  pkt[DOOR_OFFSET];
    this->light_status =  pkt[LIGHT_OFFSET];
    this->current_floor =  pkt[FLOOR_OFFSET];
    this->pid =  pkt[PID_OFFSET];
    this->temp =  pkt[TEMP_OFFSET];
    this->load = pkt[LOAD_OFFSET];
    this->person_counter = pkt[PERSON_OFFSET];
    this->maintenance = pkt[MAINTENANCE_OFFSET];
    this->direction = pkt[DIRECTION_OFFSET];
    this->moving = pkt[MOVING_OFFSET];
    this->msg_to_user = pkt[MSG_OFFSET];

    free(this->queue);
    this->byte_counter= 0;

}


void SystemServer::set_eid(uint8_t eid)
{
    this->eid = eid;
}


void SystemServer::set_door_status(uint8_t door_status)
 {
    this->door_status = door_status;
}


void SystemServer::set_light_status(uint8_t light_status)
{
    this->light_status = light_status;
}


void SystemServer::set_floor(uint8_t current_floor)
{
    this->current_floor = current_floor;
}


void SystemServer::set_pid(uint8_t pid)
{
    this->pid = pid;
}


void SystemServer::set_temp(uint8_t temp)
{
    this->temp = temp;
}


void SystemServer::set_load(uint8_t load)
{
    this->load = load;
}


void SystemServer::set_person_counter(uint8_t person_counter)
{
    this->person_counter = person_counter;
}


void SystemServer::set_msg_to_usesr(uint8_t msg_to_user)
{
    this->msg_to_user = msg_to_user;
}


uint8_t SystemServer::get_eid(void) 
{
    return this->eid;
}


uint8_t SystemServer::get_door_status(void) 
{
    return this->door_status;
}


uint8_t SystemServer::get_light_status(void) 
{
    return this->light_status;
}


uint8_t SystemServer::get_floor(void) 
{
    return this->current_floor;
}


uint8_t SystemServer::get_pid(void) 
{
    return this->pid;
}


uint8_t SystemServer::get_temp(void) 
{
    return this->temp;
}


uint8_t SystemServer::get_load(void) 
{
    return this->load;
}


uint8_t SystemServer::get_person_counter(void) 
{
    return this->person_counter;
}


uint8_t SystemServer::get_msg_to_user(void) 
{
    return this->msg_to_user;
}


uint8_t* SystemServer::get_queue(void) 
{
    return this->queue;
}


size_t SystemServer::cobs_encode(const uint8_t * input, size_t length, uint8_t * output)
{
    size_t read_index = 0;
    size_t write_index = 1;
    size_t code_index = 0;
    uint8_t code = 1;
    while(read_index < length)
    {
        output[write_index++] = input[read_index++];
        code++;
        if(code == 0xFF)
        {
            output[code_index] = code;
            code = 1;
            code_index = write_index++;
        }
    }
    output[code_index] = code;
    return write_index;
}


size_t SystemServer::cobs_decode(const uint8_t * input, size_t length, uint8_t * output)
{
    size_t read_index = 0;
    size_t write_index = 0;
    uint8_t code;
    uint8_t i;

    while(read_index < length)
    {
        code = input[read_index];

        if(read_index + code > length && code != 1)
        {
            return 0;
        }

        read_index++; /* move to packet */
        /* read all normal bytes */ 
        for(i = 1; i < code; i++)
        {
            output[write_index++] = input[read_index++];
        }
 
        // transform last encoded byte to zero
        if (code == 0xFF)
        {
            output[write_index++] = '\0';
        }
    }
    return write_index;
}