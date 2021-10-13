#pragma once
#include "Elevator.h"

class InitialState : public State {

    private:
        String stateName = "Initial";
        bool canRun = true;

    public:
        void start(Elevator* elev);
        bool canRun(); 
        void setRun(bool set);
        String currentState(){return this->stateName;}
};