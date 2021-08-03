#pragma once
#include "State.h"
#include "Elevator.h"

class EmergencyState : public State {

    private:
        String stateName = "Emergency";

    public:
        bool Emergency(Elevator* elev);
        void EmergencyWorking(Elevator* elev);

    String currentState(){return this->stateName;}
}