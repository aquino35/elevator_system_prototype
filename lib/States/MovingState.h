#pragma once
#include "State.h" 
#include "time.h"

#define UP 1
#define DOWN 0
#define undefined 3

/**
* @file MovingState.h
*
* @brief The elevator's moving state. Allows the elevator to change floors based on the elevator's
*        direction lock. 
*
* @author Yariel Mercado (Implementation & Revision)
* @author Ana Ribon (Documentation)
*/
class MovingState : public State{ 
    private:
        /* String used to identify the current state. */
        String stateName = "Moving";

        /* Boolean used to identify whether the current state can run or not. The elevator can run once a direction has been set. */
        bool run = false;

        /* Direction lock, defined as an integer and assigned by macros, with a default value of null. Up is defined as 1 and down, 0. */
        int directionLock = undefined; //up is 1, down is 0

        /* The elevator attribute. */
        Elevator* elev;

        /* A set containing the elevator's requested floors. */
        Set* stoppingFloors;

        /* Boolean used to flag whether the elevator has made a stop on a floor. */
        bool stopped = false;

        unsigned long elapsed;
        unsigned long begin; //has a conflict with start()

    public:
        MovingState(Elevator* elevator);

        void start(void);

        uint8_t  get_nearest_floor(void);

        void set_direction(void);

        bool can_run(); 

        void set_run(bool set);

        void move(void);
       
        void move_nearest(void); 

        void moving_timer(void);

        bool can_move(void);

        bool should_switch_direction(void);

        bool made_stop(void);
        
        String current_state();

        ~MovingState();

};