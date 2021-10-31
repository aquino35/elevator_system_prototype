#pragma once
#include "State.h"

class IdleState : public State{
    private:
        String stateName = "Idle";
        bool run = true;
        Elevator* elev;

    public:
        IdleState(Elevator* elevator);
        void start();
        bool canRun(); 
        void setRun(bool set);
        
        void load(uint16_t weight);
        void unload(uint16_t weight);
        void energySaving();
        String currentState(){return this->stateName;}

};