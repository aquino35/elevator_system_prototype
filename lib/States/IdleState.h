#pragma once
#include "Elevator.h"

class IdleState : public State{
    private:
        String stateName = "Idle";

    public:
        void start(Elevator* elev);
        void load(Elevator* elev, uint16_t weight);
        void unload(Elevator* elev, uint16_t weight);
        String currentState(){return this->stateName;}
};