#pragma once
#include "Elevator.h"

class IdleState : public State{
    private:
        String stateName = "Idle";
        bool run = true;

    public:
        void start(Elevator* elev);
        bool canRun(); 
        void setRun(bool set);
        
        void load(Elevator* elev, uint16_t weight);
        void unload(Elevator* elev, uint16_t weight);
        void energySaving(Elevator* elev);
        String currentState(){return this->stateName;}

};