/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include"Elevator.h"
#include"InitialState.h"
#include"IdleState.h"

class FSM {

public:

    FSM();

    void setup();

    void run(Elevator* elev);
};
