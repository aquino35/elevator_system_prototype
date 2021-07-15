/*
 * TODO : DOCUMENT
 * 
 * 
 */
#include <stdint.h>

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

    public:

        bool isDoorState(){
            return doorState;
        }

        void setDoorState(bool inputDoorST){
            doorState = inputDoorST;
        }

        double getLoadWeight(){
            return loadWeight;
        }

        void setLoadWeight(uint16_t inputLoad){
            loadWeight = inputLoad;
        }

        int getFloor(){
            return floor;
        }

        void setFloor(uint8_t inputFloor){
            floor = inputFloor;
        }

        bool isLightStatus(){
            return lightStatus;
        }

        void setLightStatus(bool inputLight){
            lightStatus = inputLight;
        }

        double getCurrentTemp(){
            return currentTemp;
        }

        void setCurrentTemp(uint8_t inputTemp){
            currentTemp = inputTemp;
        }

        double getMaxLoadWeight(){
            return maxLoadWeight;
        }

        void setMaxLoadWeight(uint16_t inputLoad){
            maxLoadWeight = inputLoad;
        }

        int getMaxFloor(){
            return maxFloor;
        }

        void setMaxFloor(uint8_t inputFloor){
            maxFloor = inputFloor;
        }

        double getMaxTemp(){
            return maxTemp;
        }

        void setMaxTemp(uint8_t inputTemp){
            maxTemp = inputTemp;
        }
};