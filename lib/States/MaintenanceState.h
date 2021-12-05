#pragma once
#include "State.h"

/**
* @file  MaintenanceState.h
*
* @brief The elevator's maintenance state. Shuts the elevator down for repairs until the elevator has been fixed.
*        Can only be activated with a special input, also used to resume operations. Processes no commands while on downtime.
*        
* @author Yariel Mercado (Implementation & Revision)
* @author Ana Ribon (Documentation)
*/
class MaintenanceState : public State{
    private:
        /* String used to identify the current state. */
        String stateName = "Maintenance";

        /* Boolean used to identify whether the current state can run or not. The elevator can run once it's been fixed. */
        bool run = false;

        /* Command used to re-active the elevator. */
        String command = "C"; 

        /* The elevator attribute. */
        Elevator* elev;
    
    public: 
        MaintenanceState(Elevator* elevator);

        void start(void);

        bool can_run(void); 

        void set_run(bool set);
        
        void show_warning(void); 

        void is_working(void); 
        
        void check(String input); 

        String current_state();

        ~MaintenanceState();
        
};