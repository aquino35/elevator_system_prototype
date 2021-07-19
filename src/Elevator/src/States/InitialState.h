#pragma once
#include <State.h> 
#include <Elevator.h>

class InitialState : public State{

    private:
        string stateName = "Initial";

    public:
        InitialState(Elevator* elev, uint8_t num, uint8_t floors);
        string currentState(){return this->stateName;}
};