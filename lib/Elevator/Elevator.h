/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include <stdint.h>
#include <Arduino.h>
class FSM; //forward declaration

// Elevator parameters
#define ELEVATOR_MAX_TEMP   120   // Maximum temperature an elevator car can reach
#define ELEVATOR_CAPACITY   10    // The max amount of people that can be stored
#define ELEVATOR_MAX_WEIGHT 1200  // The maximum allowed weight

class Elevator 
{

private:
        uint8_t eid; 
        uint8_t door_status;
        uint8_t light_status; 
        uint8_t floor;
        uint8_t max_floor;
        uint8_t current_temp;
        uint8_t max_temp;
        uint8_t capacity; 
        uint16_t load_weight; 
        uint16_t max_load_weight; //in lbs
        // State* elevator_state;
        FSM* state_machine;

public:

        // Constructors
        Elevator(uint8_t num);

        //booleans
        uint8_t is_door_status(void);

        uint8_t is_light_status(void);

        //setters
        void set_door_status(uint8_t inputDoorST);

        void set_load_weight(uint16_t inputLoad); //increases load weight

        void set_floor(uint8_t inputFloor);

        void set_light_status(uint8_t inputLight);

        void set_max_temp(uint8_t inputTemp);

        void set_current_temp(uint8_t inputTemp);

        void set_max_load_weight(uint16_t inputLoad);
    
        void set_max_floor(uint8_t inputFloor);

        // void set_state(State* nexState);

        void set_number(uint8_t num);

        //getters

        uint8_t get_number(void);
        
        uint8_t get_capacity(void);

        uint8_t get_floor(void);

        uint8_t get_max_floor(void);

        uint16_t get_load_weight(void);

        uint16_t get_max_load_weight(void);

        uint8_t get_current_temp(void);

        uint8_t get_max_temp(void);

        // String get_state_name(void);

        // State* get_state(void);

        // void run_state(void); //run the current state
};