#include "FSM.h"

FSM::FSM(Elevator* elevator)
{
    this->elev = elevator;
    State* state[5] = {new InitialState(elev), new IdleState(elev), new MovingState(elev), new EmergencyState(elev), new MaintenanceState(elev)};

    for(int i = 0; i < 5; i++){ //cant figure a way to initilaize states array 
        states[i] = state[i];
    }

}

void FSM::setup(void)
{
}

void FSM::run(void) //manages transitions
{

}

FSM::~FSM(void)
{
    delete elev;
    delete states;
}