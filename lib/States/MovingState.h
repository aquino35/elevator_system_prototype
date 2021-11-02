#pragma once
#include "State.h" 
#include "Set.h" 


class MovingState : public State{ 
    private:
        String stateName = "Moving";
        bool run = false;
        int direction_lock; //up is 1, down is 0
        uint8_t toFloor;
        Elevator* elev;

    public:
        MovingState(Elevator* elevator);
        void start();
        void setup(uint8_t floor);
        bool canRun(); 
        void setRun(bool set);
        void moving();

        String currentState(){return this->stateName;}

};