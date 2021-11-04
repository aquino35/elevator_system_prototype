#pragma once
#include "State.h"

class EmergencyState : public State {

    private:
        String stateName = "Emergency";
        bool run = false;
        Elevator* elev;

    public:
        EmergencyState(Elevator* elevator);
        void start();
        bool canRun(); 
        void setRun(bool set);

        void showWarning(); //show a warning every time a user tries to us an elevator in emergency state
        void isWorking(); //show a warning every time a user tries to us an elevator in emergency state
        void unload(uint16_t weight);

        String currentState(){return this->stateName;}
        ~EmergencyState(){};
};