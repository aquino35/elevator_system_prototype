#pragma once
#include "Elevator.h"
#include "Set.h" 

#define UP         1
#define DOWN       1

class Moving : public State{ 
    private:
        String stateName = "Moving";
        bool canRun = true;
        uint8_t direction = -1;
        uint8_t toFloor =  -1;

    public:
        void start(Elevator* elev, uint8_t floor);
        bool canRun(); 
        void setRun(bool set);
        void setRun(bool set);
        void moving(Elevator* elev, Set* stoppingFloors);

        String currentState(){return this->stateName;}

};