/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include <stdint.h>
#include <Arduino.h>
#include "State.h" 
// #include "FSM.h"


class Elevator 
{

private:

        bool doorStatus, lightStatus; //false means closed and lights off
        uint8_t floor, maxFloor;
        uint8_t currentTemp, maxTemp, elevatorNumber; //temp in F
        uint16_t loadWeight, maxLoadWeight; //in lbs
        State* elevatorState;
        //FSM* stateMachine;

public:

        // Constructors
        Elevator(uint8_t num);

        //booleans
        bool isDoorStatus();

        bool isLightStatus();

        //setters
        void setDoorStatus(bool inputDoorST);

        void setLoadWeight(uint16_t inputLoad); //increases load weight

        void setFloor(uint8_t inputFloor);

        void setLightStatus(bool inputLight);

        void setMaxTemp(uint8_t inputTemp);

        void setCurrentTemp(uint8_t inputTemp);

        void setMaxLoadWeight(uint16_t inputLoad);
    
        void setMaxFloor(uint8_t inputFloor);

        void setState(State* nexState);

        void setNumber(uint8_t num);

        //getters
        uint16_t getLoadWeight();

        uint8_t getFloor();

        uint8_t getCurrentTemp();

        uint16_t getMaxLoadWeight();

        uint8_t getMaxFloor();

        uint8_t getMaxTemp();

        String getStateName();

        State* getState();

        uint8_t getNumber();
};