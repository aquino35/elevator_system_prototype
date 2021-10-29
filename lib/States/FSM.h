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

#define INITIAL_OFFSET      0
#define IDLE_OFFSET         1
#define MOVING_OFFSET       2
#define EMERGENCY_OFFSET    3
#define MAINTENANCE_OFFSET  4

#define ELEV_1_OFFSET   0
#define ELEV_2_OFFSET   1



class FSM {
    private:
        Elevator* elevators[4];
        State* states[5] = {new InitialState(), new IdleState(), new MovingState(), new EmergencyState(), new MaintenanceState()};

    public:
        FSM(Elevator* elev1, Elevator* elev2); //initialize elevators
        void setup(void); //put elevs in initial state
        void run(void); //run each elevator
        ~FSM(void); //end FSM
};
