#pragma once
#include "AllStates.h"
#include "SystemServer.h"

/* Macros, used to map the FSM's commands. */

#define null              0
#define INITIAL_STATE     1
#define IDLE_STATE        2
#define MOVING_STATE      3
#define EMERGENCY_STATE   4
#define MAINTENANCE_STATE 5

#define LOAD_COMMAND                 7
#define UNLOAD_COMMAND               8
#define MOVE_COMMAND                 9
#define MAINTENANCE_COMMAND          10
#define FIX_MAINTENANCE_COMMAND      13

#define MADE_STOP                 20
#define LOADED                    21
#define UNLOADED                  22
#define EMERGENCY                 23
#define ENERGY_SAVING             24
#define IDLE                      25
#define MAINTENANCE               26
#define MOVED                     27
#define CHANGED_DIRECTION         28
#define INITIAL                   29
#define ERROR                     40


/**
* @file FSM.h
*
* @brief The Finite State Machine manages an individual elevator and allows it function, based on the input commands it recieves.
*
* @author Yariel Mercado (Implementation & Revision)
* @author Ana Ribon (Documentation)
*/
class FSM {
    private:
        /* The FSM's initial state attribute. */
        InitialState* initialState; 
        /* The FSM's idle state attribute. */
        IdleState* idleState;
        /* The FSM's moving state attribute. */
        MovingState* movingState;
        /* The FSM's emergency state attribute. */
        EmergencyState* emergencyState; 
        /* The FSM's maintenance state attribute. */
        MaintenanceState* maintenanceState;

        /* The elevator attribute. */
        Elevator* elev;

        /* Keeps track of the current state, an integer, denoted by that states macro variable.*/
        int currState = null; 

        unsigned long elapsed;
        unsigned long start;

        /* Boolean representing whether the elevator has been recently used or not. Helps keep track of when to activate energy saving mode.*/
        bool toggle = false; 

        /* Transmits data between the FSM and the server. */
        SystemServer* server;

        uint8_t message;

        Set* people_in;


    public:
        FSM(Elevator* elevator); 

        void setup(void);

        void run(int command); 
        
        void energy_update();

        void warning();

        void emergency_toggle();

        void moving_loop();

        void update_server();

        void load_in();
        
        void unload_person();

        ~FSM(); 
};

