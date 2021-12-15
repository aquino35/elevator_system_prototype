#include "Elevator.h"

/**
* The elevator constructor. Creates an elevator and assigns it an ID based off the given parameter.
* Defines the elevator's allowable, working parameters and sets its current floor to the first.
*
* @param num The elevator's unique ID.
*/
Elevator::Elevator(uint8_t num)
{
    eid = num;
    maxLoad = ELEVATOR_MAX_WEIGHT;
    maxTemp = ELEVATOR_MAX_TEMP;
    capacity = ELEVATOR_CAPACITY;
    floor = 1;
}

/**
* Sets the elevator's door status to either open or closed based on the boolean parameter.
*
* @param inputDoorST A boolean indicating whether the elevator's doors are open or closed, 
*                    true and false respectively.
*/
void Elevator::set_door_status(bool inputDoorST)
{
    this->doorStatus = inputDoorST;
}

/**
* Increases the elevator's load weight, in pounds, based on the given parameter.
*
* @param inputLoad The amount of weight to be loaded onto the elevator.
*/
void Elevator::set_load_weight(uint16_t inputLoad)
{
    this->loadWeight = inputLoad; 
}

/**
* Sets the elevator's current floor to the given parameter.
*
* @param inputFloor The floor the elevator will transition to.
*/
void Elevator::set_floor(uint8_t inputFloor)
{
    this->floor = inputFloor;
}

/**
* Sets the elevator's light status based on the boolean parameter.
*
* @param inputLight A boolean indicating whether the elevator's internal lights will be on or off,
*                   true or false, respectively.
*/
void Elevator::set_light_status(bool inputLight)
{
    this->lightStatus = inputLight;
}

/**
* Sets the elevator's maximum allowable temperature, in fahrenheit, based on the given parameter.
*
* @param inputTemp The elevators maximum allowable temperature.
*/
void Elevator::set_max_temp(uint8_t inputTemp)
{
    this->maxTemp = inputTemp;
}

/**
* Sets the elevator's current temperature, in fahrenheit, based on the given parameter.
*
* @param inputTemp The elevators current temperature.
*/
void Elevator::set_current_temp(uint8_t inputTemp)
{
    this->currentTemp = inputTemp;
}

/**
* Sets the elevator's maximum load weight, in pounds, based on the given parameter.
*
* @param inputLoad The elevators maxmimum allowable weight, in pounds.
*/
void Elevator::set_max_load_weight(uint16_t inputLoad)
{
    this->maxLoad = inputLoad;
}

/**
* Sets the buildings highest floor, based off the input parameter.
*
* @param inputFloor The highest floor the elevator can reach.
*/
void Elevator::set_max_floor(uint8_t inputFloor)
{
    this->maxFloor = inputFloor;
}

/**
* Specifies to the elevator the currently requested floors based off of the parameter set.
*
* @param floors A set containing the elevator's currently requested floors.
*/
void Elevator::set_stopping_floors(Set* floors)
{
    this->stoppingFloors = floors;
}

/**
* Determines whether the elevators doors are open or closed based on the elevator's boolean attribute.
*
* @return A boolean specifying whether the elevators doors are open or closed, true or false, respectively.
*/
bool Elevator::is_door_open(void)
{
    return doorStatus;
}

/**
* Determines whether the elevators lights are on or off based on the elevator's boolean attribute.
*
* @return A boolean specifying whether the elevators lights are on or off, true or false, respectively.
*/
bool Elevator::is_light_on(void)
{
    return lightStatus;
}

/**
* Retrieves the elevator's ID.
*
* @return An integer, as a uint8_t, representing the elevator's numerical ID.
*/
uint8_t Elevator::get_number(void)
{
    return eid;
}

/**
* Retrieves the elevator's capacity.
*
* @return An integer, as a uint8_t, representing the amount of people on the elevator.
*/
uint8_t Elevator::get_capacity(void)
{
    return capacity;
}

/**
* Retrieves the elevator's current floor.
*
* @return An integer, as a uint8_t, representing the current floor the elevator is on.
*/
uint8_t Elevator::get_floor(void)
{
    return floor;
}

/**
* Retrieves the building's highest floor.
*
* @return An integer, as a uint8_t, representing the highest reachable floor in the building by the elevator.
*/
uint8_t Elevator::get_max_floor(void)
{
    return maxFloor;
}

/**
* Retrieves the elevator's current load weight, in pounds.
*
* @return An integer, as a uint16_t, representing the elevator's current load weight in pounds.
*/
uint16_t Elevator::get_load_weight(void)
{
    return loadWeight;
}

/**
* Retrieves the elevator's maximum allowable load weight, in pounds.
*
* @return An integer, as a uint16_t, representing the elevator's maximum allowable load weight in pounds.
*/
uint16_t Elevator::get_max_load_weight(void)
{
    return maxLoad;
}

/**
* Retrieves the elevator's current internal temperature, in fahrenheit.
*
* @return An integer, as a uint8_t, representing the elevator's internal temperature, in fahrenheit.
*/
uint8_t Elevator::get_current_temp(void)
{
    return currentTemp;
}

/**
* Retrieves the elevator's maximum allowable internal temperature, in fahrenheit.
*
* @return An integer, as a uint8_t, representing the elevator's maximum allowable internal temperature, in fahrenheit.
*/
uint8_t Elevator::get_max_temp(void)
{
    return maxTemp;
}

/**
* Retrieves the elevator's set of currently requested floors.
*
* @return A set, containing the elevator's currently requested floors.
*/
Set* Elevator::get_stopping_floors(void)
{
    return stoppingFloors;
}

uint8_t Elevator::get_people(){
    return num_people;
}

/**
* An elevator command, which forces its doors open by setting the necessary boolean attribute to true.
*/
void Elevator::open(void)
{
    set_door_status(true);
}

/**
* An elevator command, which closes its doors by setting the necessary boolean attribute to false.
*/
void Elevator::close()
{
    set_door_status(false);
}

/**
* An elevator command, which turns its lights on by setting the necessary boolean attribute to true.
*/
void Elevator::turn_lights_on()
{
    set_light_status(true);
}

/**
* An elevator command, which turns its lights off by setting the necessary boolean attribute to false.
*/
void Elevator::turn_lights_off()
{
    set_light_status(false);
}

person* Elevator::load_people_in(){
    person* human = new Person(random(1, 4));
    num_people++;
    return human;
}

/**
* Elevator destructor. Deletes the set of currently requested floors: the elevator's only
* instance of dynamically allocated memory.
*/
Elevator::~Elevator()
{
    delete stoppingFloors;
}