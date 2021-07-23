/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "State.h" 

class Elevator {

private:
        bool doorStatus, lightStatus; //false means closed and lights off
        uint8_t floor, maxFloor;
        uint8_t currentTemp, maxTemp, elevatorNumber; //temp in F
        uint16_t loadWeight = 0; //so we can increment the loads
        uint16_t maxLoadWeight; //in lbs

        State* elevatorState; 
        
        vector<uint16_t> weights; //keeps track of all the loads in the elevator; 
        //code wont compile, pick a more clever approach or data structure

public:
        // Constructors
        Elevator();

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

        String getState();

        //functions
        void unload();
};