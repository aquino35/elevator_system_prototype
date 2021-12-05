#include "InitialState.h"

/**
* Contructor for the moving state. Initializes with the given elevator as a parameter.
*
* @param elevator The elevator being initialized in the current state.
*/
InitialState::InitialState(Elevator* elevator){
    this->elev = elevator;
}

/**
* Initializes the elevator's default attributes.
*/ 
void InitialState::start(void)
{
    elev->set_load_weight(0);
    elev->close();
    elev->turn_lights_on();
    elev->set_floor(1);
    elev->set_current_temp(60);
    Serial.println("ELEVATOR #" + String(elev->get_number()) + " INITIALIZED!");
}

/**
*  Returns a boolean indicating wether the current state can run. 
*
* @return A boolean, indicating whether the elevator can run or not.
*/ 
bool InitialState::can_run(void){
    return this->run;
}

/**
*  Receives a boolean and sets the state's current run attribute, denoting whether the state can be run. 
*
* @param set Sets the state's run attribute to the given boolean parameter.
*/ 
void InitialState::set_run(bool set){
    this->run = set;
}


/**
*  Identifies the current state's name. 
*
* @return The current state's name, as a String.
*/ 
String InitialState::current_state()
{
    return this->stateName;
}

/**
*  The state's destructor. The elevator is cleared out in the Finite State Machine.
*/ 
InitialState::~InitialState(){};