#pragma once
#include "State.h" 
#include "Set.h" 
#include "time.h"

#define UP 1
#define DOWN 0

class MovingState : public State{ 
    private:
        String stateName = "Moving";
        bool run = false;
        int direction_lock = NULL; //up is 1, down is 0
        uint8_t toFloor;
        Elevator* elev;
        bool stopped = false;

        clock_t begin;
        double time_spent;

    public:
        MovingState(Elevator* elevator);
        void start();
        uint8_t get_nearest_floor();
        void set_direction();
        bool canRun(); 
        void setRun(bool set);
        void move();
        void move_nearest(); 
        void moving_timer();
        bool canMove();
        bool should_switch_direction();
        bool made_stop();

        String currentState(){return this->stateName;}

};