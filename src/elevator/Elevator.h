/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include <stdint.h>
#include <string>

class Elevator {

    private:
        bool doorState;
        uint16_t loadWeight;
        uint8_t floor;
        bool lightStatus;
        uint8_t currentTemp;
        uint16_t maxLoadWeight;
        uint8_t maxFloor;
        uint8_t maxTemp;

        State* elevatorState; 

    public:

        //booleans
        bool isDoorState(){
            return doorState;
        }

        bool isLightStatus(){
            return lightStatus;
        }

        //setters
        void setDoorState(bool inputDoorST){
            doorState = inputDoorST;
        }
        
        void setLoadWeight(uint16_t inputLoad){
            loadWeight = inputLoad;
        }

        void setFloor(uint8_t inputFloor){
            floor = inputFloor;
        }


        void setLightStatus(bool inputLight){
            lightStatus = inputLight;
        }

        void setMaxTemp(uint8_t inputTemp){
            maxTemp = inputTemp;
        }

        void setCurrentTemp(uint8_t inputTemp){
            currentTemp = inputTemp;
        }

        void setMaxLoadWeight(uint16_t inputLoad){
            maxLoadWeight = inputLoad;
        }

        void setMaxFloor(uint8_t inputFloor){
            maxFloor = inputFloor;
        }

        void setState(State& nexState){
            elevatorState = nextState;
        }

        //getters
        uint16_t getLoadWeight(){
            return loadWeight;
        }

        uint8_t getFloor(){
            return floor;
        }

        uint8_t getCurrentTemp(){
            return currentTemp;
        }

        
       uint16_t getMaxLoadWeight(){
            return maxLoadWeight;
        }

        uint8_t getMaxFloor(){
            return maxFloor;
        }

        uint8_t getMaxTemp(){
            return maxTemp;
        }

        string getState(){
            return elevatorState->currentState();
        }

};