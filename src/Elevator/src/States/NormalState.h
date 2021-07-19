#pragma once
#include <string>
#include <State.h> 
#include <Elevator.h>

class NormalState : public State{

    private:
        string stateName = "Normal";

    public:
        NormalState(Elevator* elev, uint8_t num, uint8_t floors);
        string currentState(){return this->stateName;}

};