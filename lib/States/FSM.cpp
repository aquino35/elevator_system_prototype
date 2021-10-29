#include "FSM.h"

FSM::FSM(Elevator* elev1, Elevator* elev2)
{
    if(elev1 != NULL){
        elevators[ELEV_1_OFFSET] = elev1;
    }

    if(elev2 != NULL){
        elevators[ELEV_2_OFFSET] = elev2;
    }
}

void FSM::setup(void)
{
    for(int i = 0; i < 2; i++){ //initializes elevators in InitialState
        elevators[i]->set_state(states[INITIAL_OFFSET]);
        elevators[i]->run_state();
    }

    for(int i = 0; i < 2; i++){ //transition to IdleState
        elevators[i]->set_state(states[IDLE_OFFSET]);
    } 
}

void FSM::run(void) //manages transitions
{

}

FSM::~FSM(void)
{
    delete elevators;
    delete states;
}