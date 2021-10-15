#pragma once
#include "Elevator.h"

class Moving : public State{ 
    /***
     * IDEAS
     * 
     * Because of the direction lock, implement the floors as a stack so you can add floors when going up, and pop them top to bottom when going down
     * 
     * */
    private:
        String stateName = "Moving";
        bool canRun = true;
        uint8_t toFloor;

    public:
        void start(Elevator* elev, uint8_t floor);
        bool canRun(); 
        void setRun(bool set);
        
        void movingCycle(Elevator* elev);
        String currentState(){return this->stateName;}

};