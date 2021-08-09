#pragma once
#include "Arduino.h"

class State{

    public:
        virtual String currentState() = 0; 
        // virtual void start(Elevator* elev) =  0; //acts as an initializer of sorts for the state
};