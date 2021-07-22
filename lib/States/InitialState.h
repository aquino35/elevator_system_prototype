#pragma once
#include "State.h"
#include "Elevator.h"

class InitialState : public State {

    private:
        String stateName = "Initial";

    public:
        InitialState(){}; //needs a default constructor
        InitialState(Elevator* elev, uint8_t num, uint8_t floors, uint8_t temp);
        String currentState(){return this->stateName;}
};