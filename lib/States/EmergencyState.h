#pragma once
#include "Elevator.h"

class EmergencyState : public State {

    private:
        String stateName = "Emergency";
        bool canRun = false;

    public:
        void start(Elevator* elev);
        bool canRun(); 
        void setRun(bool set);
        void showWarning(); //show a warning every time a user tries to us an elevator in emergency state
        String currentState(){return this->stateName;}
};