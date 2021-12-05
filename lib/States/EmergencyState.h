#pragma once
#include "State.h"

/**
* @file EmergencyState.h
*
* @brief The elevator enters a state of emergency when its parameters exceed their maximum established values.
*        Changes to the nearest floor and re-establishes parameters back to their default values.
*        
* @author Yariel Mercado (Implementation & Revision)
* @author Ana Ribon (Documentation)
*/
class EmergencyState : public State {
    private:
        /* String used to identify the current state. */
        String stateName = "Emergency";

        /* Boolean used to identify whether the current state can run or not. The elevator can run once parameters normalize. */
        bool run = false;

        /* The elevator attribute. */
        Elevator* elev;

    public:
        EmergencyState(Elevator* elevator);

        void start(void);

        bool can_run(void); 

        void set_run(bool set);

        void show_warning(void); 

        void is_working(void); 

        void unload(uint8_t weight);

        String current_state(); 

        ~EmergencyState();
};