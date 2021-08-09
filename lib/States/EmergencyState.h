#pragma once
#include "Elevator.h"

class EmergencyState : public State {

    private:
        String stateName = "Emergency";

    public:
        void start(Elevator* elev);
        bool emergency(Elevator* elev);
        void emergencyWorking(Elevator* elev);
        String currentState(){return this->stateName;}
};