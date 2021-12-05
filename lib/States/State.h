#pragma once
#include "Elevator.h"

/**
* @file State.h
*
* @brief Abstract class for all of the elevator's states.
*
* @author Yariel Mercado (Implementation & Revision)
* @author Ana Ribon (Documentation)
*/
class State{
    public:
        /* String used to identify the current state. */
        virtual String current_state(void) = 0; 

        /* Boolean used to identify if a state can be run or not. */
        virtual bool can_run(void) = 0; 

        /* Boolean used to set whether the state can be run or not. */
        virtual void set_run(bool set) = 0;  

        /* Allows each state to initialize. */
        virtual void start() =  0; 

        /* Abstract destructor which must be inherited by the states. Else, the derived states aren't safely deleted. */
        virtual ~State() = 0;
};
