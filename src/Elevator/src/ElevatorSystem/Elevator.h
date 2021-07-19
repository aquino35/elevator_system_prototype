/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include <stdint.h>
//#include <string>

class Elevator {

private:
        bool doorState, lightStatus;
        uint8_t floor, maxFloor;
        uint8_t currentTemp, maxTemp;
        uint16_t loadWeight, maxLoadWeight;

        //State* elevatorState; 

public:
        // Constructors
        Elevator();

        //booleans
        bool isDoorState();

        bool isLightStatus();

        //setters
        void setDoorState(bool inputDoorST);

        void setLoadWeight(uint16_t inputLoad);

        void setFloor(uint8_t inputFloor);

        void setLightStatus(bool inputLight);

        void setMaxTemp(uint8_t inputTemp);

        void setCurrentTemp(uint8_t inputTemp);

        void setMaxLoadWeight(uint16_t inputLoad);
    
        void setMaxFloor(uint8_t inputFloor);

        //void setState(State& nexState);

        //getters
        uint16_t getLoadWeight();

        uint8_t getFloor();

        uint8_t getCurrentTemp();

        uint16_t getMaxLoadWeight();

        uint8_t getMaxFloor();

        uint8_t getMaxTemp();

        //std::string getState();
};