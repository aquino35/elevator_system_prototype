/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include "AllStates.h"

#define INITIAL_OFFSET      0
#define IDLE_OFFSET         1
#define MOVING_OFFSET       2
#define EMERGENCY_OFFSET    3
#define MAINTENANCE_OFFSET  4


class FSM {
    private:
        Elevator* elev;
        State* states[5];

    public:
        FSM(Elevator* elevator); //initialize elevators
        void setup(void); //put elevs in initial state
        void run(void); //run each elevator
        ~FSM(void); //end FSM
};
