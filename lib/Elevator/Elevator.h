#pragma once
#include "SystemServer.h"
#include "Set.h"

/* Elevator Parameter Macros */
#define ELEVATOR_MAX_TEMP   120   // Maximum temperature an elevator car can reach
#define ELEVATOR_CAPACITY   10    // The max amount of people that can be stored
#define ELEVATOR_MAX_WEIGHT 1200  // The maximum allowed weight

typedef struct Person{
    uint16_t weight;
    uint8_t temp;
    String identifer; 

    Person(uint8_t type){
        switch(type){
            case 1:
                weight = 160;
                temp = 5;
                identifer = "Adult";
                break;

            case 2:
                weight = 50;
                temp = 3;
                identifer = "Child";
                break;

            case 3:
                weight = 135;
                temp = 4;
                identifer = "Elderly";
                break;
        }

    }
}person;

/**
* @file Elevator.h
*
* @brief The elevator class. Contains its attributes, commands, and more.
*
* @author Yariel Mercado (Implementation & Documentation)
* @author Osvaldo Aquino (Implementation)
*/
class Elevator {
    private:
        /* The elevator's ID. */
        uint8_t eid; 
        /* Boolean determining whether a door is open or closed. */
        bool doorStatus;
        /* Boolean determining whether the elevator lights are on or off. */
        bool lightStatus; 
        /* The elevator's current floor. */
        uint8_t floor;
        /* The last and highest floor in the elevator's building. */
        uint8_t maxFloor;
        /* The elevator's current temperature, in fahrenheit. */
        uint8_t currentTemp;
        /* The elevator's maximum allowable temperature, in fahrenheit. */
        uint8_t maxTemp;
        /* The amount of people the elevator is carrying. */
        uint8_t capacity; 
        /* The elevator's current weight, in pounds. */
        uint16_t loadWeight; 
        /* The elevator's maximum allowable weight, in pounds. */
        uint16_t maxLoad; 
        /* Set containing the elevator's requested floors. */
        Set* stoppingFloors;

    public:
        Elevator(uint8_t num);
        ~Elevator();

        /* Setters */

        void set_door_status(bool inputDoorST);

        void set_load_weight(uint16_t inputLoad); 

        void set_floor(uint8_t inputFloor);

        void set_light_status(bool inputLight);

        void set_max_temp(uint8_t inputTemp);

        void set_current_temp(uint8_t inputTemp);

        void set_max_load_weight(uint16_t inputLoad);
    
        void set_max_floor(uint8_t inputFloor);

        void set_stopping_floors(Set* floors);

        /* Getters */
        
        bool is_door_open(void);

        bool is_light_on(void);

        uint8_t get_number(void);
        
        uint8_t get_capacity(void);

        uint8_t get_floor(void);

        uint8_t get_max_floor(void);

        uint16_t get_load_weight(void);

        uint16_t get_max_load_weight(void);

        uint8_t get_current_temp(void);

        uint8_t get_max_temp(void);

        Set* get_stopping_floors(void);

        /* Specific actions */

        void open(void);

        void close(void);

        void turn_lights_on();

        void turn_lights_off();
};