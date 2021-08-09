#pragma once
#include "Elevator.h"

class InitialState : public State {

    private:
        String stateName = "Initial";

    public:
        void start(Elevator* elev);
        String currentState(){return this->stateName;}
};