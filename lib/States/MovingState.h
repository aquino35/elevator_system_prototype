#pragma once
#include "State.h" 
#include "Set.h" 

#define UP         1
#define DOWN       1

class MovingState : public State{ 
    private:
        String stateName = "MovingState";
        bool run = false;
        int direction;
        uint8_t toFloor;
        Elevator* elev;

    public:
        MovingState(Elevator* elevator);
        void start();
        void setup(uint8_t floor);
        bool canRun(); 
        void setRun(bool set);
        void moving(Set* stoppingFloors);

        String currentState(){return this->stateName;}

};