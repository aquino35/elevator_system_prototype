#pragma once
#include "Elevator.h"
#include <time.h>

class IdleState : public State{
    private:
        String stateName = "Idle";
        Elevator* elev;
        time_t start;

    public:
        IdleState(Elevator* elev);
        void load(uint16_t weight);
        void unload(uint16_t weight);
        void tick();
        String currentState(){return this->stateName;}
};