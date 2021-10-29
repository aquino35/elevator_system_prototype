#pragma once
#include "Elevator.h"
#include "Set.h" 

#define UP         1
#define DOWN       1

class MovingState : public State{ 
    private:
        String stateName = "MovingState";
        bool run = false;
        int direction;
        uint8_t toFloor;

    public:
        void start(Elevator* elev);
        void setup(Elevator* elev, uint8_t floor);
        bool canRun(); 
        void setRun(bool set);
        void moving(Elevator* elev, Set* stoppingFloors);

        String currentState(){return this->stateName;}

};