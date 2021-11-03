/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include "AllStates.h"
#include "time.h"

class FSM {
    private:
        //states
        InitialState* initial_state; 
        IdleState* idle_state;
        MovingState* moving_state;
        EmergencyState* emergency_state; 
        MaintenanceState* maintenance_state;

        Elevator* elev;
        String currentStateName = ""; //keeps track of the current state

        clock_t begin;
        double time_spent;
        bool toggle = false; //for energy saving


    public:
        FSM(Elevator* elevator); //initialize elevators
        void setup(void); //put elevs in initial state
        void run(uint8_t command); //run each elevator
        void energyUpdate();
        ~FSM(); //end FSM
};
