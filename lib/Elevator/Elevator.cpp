#include "Elevator.h"

//Constructor
Elevator::Elevator(uint8_t num){
    setNumber(num);
    setMaxLoadWeight(2500);
    setMaxTemp(90);
    //this->statemachine = new FSM();

}

//booleans
bool Elevator::isDoorStatus(){
    return doorStatus;
}

bool Elevator::isLightStatus(){
    return lightStatus;
}

//setters
void Elevator::setDoorStatus(bool inputDoorST){
    this->doorStatus = inputDoorST;
}

void Elevator::setLoadWeight(uint16_t inputLoad){
    this->loadWeight = inputLoad; //change based on data structure
}

void Elevator::setFloor(uint8_t inputFloor){
    this->floor = inputFloor;
}

void Elevator::setLightStatus(bool inputLight){
    this->lightStatus = inputLight;
}

void Elevator::setMaxTemp(uint8_t inputTemp){
    this->maxTemp = inputTemp;
}

void Elevator::setCurrentTemp(uint8_t inputTemp){
    this->currentTemp = inputTemp;
}

void Elevator::setMaxLoadWeight(uint16_t inputLoad){
    this->maxLoadWeight = inputLoad;
}

void Elevator::setMaxFloor(uint8_t inputFloor){
    this->maxFloor = inputFloor;
}

void Elevator::setState(State* nextState){
    this->elevatorState = nextState;
}

void Elevator::setNumber(uint8_t num){
    elevatorNumber = num;         
}

//getters
uint16_t Elevator::getLoadWeight(){
    return loadWeight;
}

uint8_t Elevator::getFloor(){
    return floor;
}

uint8_t Elevator::getCurrentTemp(){
    return currentTemp;
}

uint16_t Elevator::getMaxLoadWeight(){
    return maxLoadWeight;
}

uint8_t Elevator::getMaxFloor(){
    return maxFloor;
}

uint8_t Elevator::getMaxTemp(){
    return maxTemp;
}

String Elevator::getStateName(){
    return elevatorState->currentState();
}

State* Elevator::getState(){
    return elevatorState;
}

uint8_t Elevator::getNumber(){
    return elevatorNumber;
}