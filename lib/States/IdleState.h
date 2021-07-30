#pragma once
#include "Elevator.h"

class IdleState : public State{
    private:
        String stateName = "Idle";
        Elevator* elev;

    public:
        IdleState(Elevator* elev);
        void load(uint16_t weight);
        void unload(uint16_t weight);
        String currentState(){return this->stateName;}
};