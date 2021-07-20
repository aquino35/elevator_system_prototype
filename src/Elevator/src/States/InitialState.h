#pragma once
#include "State.h"
#include "ElevatorSystem/Elevator.h"

class InitialState : public State{

    private:
        string stateName = "Initial";

    public:
        InitialState(Elevator* elev, uint8_t num, uint8_t floors, uint8_t temp);
        string currentState(){return this->stateName;}
};