/*
 * TODO : DOCUMENT
 * 
 * 
 */
#pragma once
#include<stdlib.h>
#include"elevator.h"
#include"InitialState.h"
#include"IdleState.h"

class FSM {

public:

    FSM();

    void setup();

    void run(Elevator* elev);
};
