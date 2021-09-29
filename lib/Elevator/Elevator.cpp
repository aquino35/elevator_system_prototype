#include "Elevator.h"

//Constructor
Elevator::Elevator(uint8_t num)
{
    eid = num;
    max_load_weight = ELEVATOR_MAX_WEIGHT;
    max_temp = ELEVATOR_MAX_TEMP;
    capacity = ELEVATOR_CAPACITY;
    //this->statemachine = new FSM();
}

//booleans
uint8_t Elevator::is_door_status(void)
{
    return door_status;
}

uint8_t Elevator::is_light_status(void)
{
    return light_status;
}

//setters
void Elevator::set_door_status(uint8_t inputDoorST)
{
    this->door_status = inputDoorST;
}

void Elevator::set_load_weight(uint16_t inputLoad)
{
    this->load_weight = inputLoad; //change based on data structure
}

void Elevator::set_floor(uint8_t inputFloor)
{
    this->floor = inputFloor;
}

void Elevator::set_light_status(uint8_t inputLight)
{
    this->light_status = inputLight;
}

void Elevator::set_max_temp(uint8_t inputTemp)
{
    this->max_temp = inputTemp;
}

void Elevator::set_current_temp(uint8_t inputTemp)
{
    this->current_temp = inputTemp;
}

void Elevator::set_max_load_weight(uint16_t inputLoad)
{
    this->max_load_weight = inputLoad;
}

void Elevator::set_max_floor(uint8_t inputFloor)
{
    this->max_floor = inputFloor;
}

void Elevator::set_state(State* nextState)
{
    this->elevator_state = nextState;
}

void Elevator::set_number(uint8_t num)
{
    eid = num;         
}

//getters


uint8_t Elevator::get_number(void)
{
    return eid;
}


uint8_t Elevator::get_capacity(void)
{
    return capacity;
}

uint8_t Elevator::get_floor(void)
{
    return floor;
}

uint8_t Elevator::get_max_floor(void)
{
    return max_floor;
}

uint16_t Elevator::get_load_weight(void)
{
    return load_weight;
}

uint16_t Elevator::get_max_load_weight(void)
{
    return max_load_weight;
}

uint8_t Elevator::get_current_temp(void)
{
    return current_temp;
}

uint8_t Elevator::get_max_temp(void)
{
    return max_temp;
}

String Elevator::get_state_name(void)
{
    return elevator_state->currentState();
}

State* Elevator::get_state(void)
{
    return elevator_state;
}
