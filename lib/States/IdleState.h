#pragma once
#include "State.h"
#include "Elevator.h"

class IdleState : public State{
    private:
        String stateName = "Idle";

    public:
        IdleState(){};
        String currentState(){return this->stateName;}
};