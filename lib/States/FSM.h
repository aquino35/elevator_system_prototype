/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include "AllStates.h"
#include "time.h"

#define INITIAL_OFFSET      0
#define IDLE_OFFSET         1
#define MOVING_OFFSET       2
#define EMERGENCY_OFFSET    3
#define MAINTENANCE_OFFSET  4


class FSM {
    private:
        Elevator* elev;
        State* states[5];
        String currentState; //keeps track of the current state
        State* current_state;

        clock_t begin;
        double time_spent;


    public:
        FSM(Elevator* elevator); //initialize elevators
        void setup(void); //put elevs in initial state
        void run(uint8_t command); //run each elevator
        ~FSM(); //end FSM
};
