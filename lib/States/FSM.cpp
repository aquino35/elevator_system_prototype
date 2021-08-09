/*
 * TODO : DOCUMENT
 * 
 * 
 */

#include<FSM.h>

typedef enum {
    Initial=0,
    Emergency,
    Maintenence,
    Idle,
    Moving
} StateNames; 

StateNames curr_state; // used to keep track of the current state of the elevator

int transition; // temporary (used to test transition between states)

// Helper Functions used to connect State Objects
void _Initial(Elevator* elev)
{
    InitialState* initialState = new InitialState();
    elev->setState(initialState);
    initialState->start(elev);
    transition++;
    if (transition == 2) {
        curr_state = Idle;
    }
}

void _Emergency(Elevator* elev)
{
    Serial.println("Emergency");
}

void _Maintenece(Elevator* elev){}

void _Idle(Elevator* elev)
{
    IdleState* idleState = new IdleState();
    elev->setState(idleState);
    idleState->start(elev);
}

void _Moving(Elevator* elev){}

// an array of pointer functions to map each state to its proper helper function
static void (*state_table[])(Elevator* elev) = { _Initial, _Emergency, _Maintenece, _Idle, _Moving};

//Constructor
FSM::FSM(){}

void FSM::setup(){
    curr_state = Initial;
    transition = 1;
}

void FSM::run(Elevator* elev){
    state_table[curr_state](elev);
    transition++;
}