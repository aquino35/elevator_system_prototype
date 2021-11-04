#pragma once
#include "State.h"

class InitialState : public State {

    private:
        String stateName = "Initial";
        bool run = true;
        Elevator* elev;

    public:
        InitialState(Elevator* elevator);
        void start();
        bool canRun(); 
        void setRun(bool set);
        String currentState(){return this->stateName;}
        ~InitialState(){};
};