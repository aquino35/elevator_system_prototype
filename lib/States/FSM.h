/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include "InitialState.h"
#include "IdleState.h"
#include "MaintenanceState.h"
#include "MovingState.h"
#include "EmergencyState.h"

class FSM {
    private:
        Elevator* elev;
        State* states[5] = {new InitialState(), new IdleState(), new MovingState(), new EmergencyState(), new MaintenanceState()};

    public:
        FSM(Elevator* elevator);
        void setup();
        void run(Elevator* elev);
};
