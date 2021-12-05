#include "EmergencyState.h"

/**
* Contructor for the moving state. Initializes with the given elevator as a parameter.
*
* @param elevator The elevator being initialized in the current state.
*/
EmergencyState::EmergencyState(Elevator* elevator){
    this->elev = elevator;
}

/**
* Activates the state by opening the doors and turning the lights on, in order to stabilize the elevator.
*/ 
void EmergencyState::start(void){
    elev->open();
    elev->turn_lights_on();
    Serial.println("ENTERING EMERGENCY STATE! NO COMMANDS WILL BE PROCESSED UNTIL ELEVATOR #" + String(elev->get_number()) + " STABILIZES!");
    this->show_warning();
}

/**
* In order to stabilize the weight, the whole elevator must be emptied out. Thus the need for a custom unloading function.
*
* @param weight The weight to be unloaded, in pounds.
*/ 
void EmergencyState::unload(uint8_t weight){
    uint8_t toUnload = elev->get_load_weight() - weight;
    elev->set_load_weight(toUnload);
}

/**
* Prints a warning to the terminal, showcasing all of the parameter differences. Informs the elevator
* system manager of which elevator attributes must stabilize.
*
*/ 
void EmergencyState::show_warning(void){
    Serial.println("PARAMETERS MUST GO BACK TO THE MAXIMUM ALLOWED VALUES!" );
    Serial.println();
    Serial.println("PARAMETER DIFFERENCES:");
    Serial.println("----------------------");

    if(elev->get_current_temp() > elev->get_max_temp()){
        Serial.println("TEMP IS " + String(elev->get_current_temp()) + " DEGREES F! MUST LOWER BY: " + String(elev->get_current_temp()-elev->get_max_temp()) + " DEGREES F!" );
    }

    else if(elev->get_current_temp() <= elev->get_max_temp()){
        Serial.println("TEMP IS NORMAL!");
    }

    if(elev->get_load_weight() > elev->get_max_load_weight()){
        Serial.println("CURRENT CAPACITY IS " + String(elev->get_load_weight()) + " POUNDS! MUST LOWER BY: " + String(elev->get_load_weight()-elev->get_max_load_weight()) + " POUNDS!" );
    }

    else if(elev->get_load_weight() <= elev->get_max_load_weight()){
        Serial.println("CAPACITY IS NORMAL!");
    }
    
}

/**
* Checks whether the parameters are within the alloted values. Else, displays a warning.
*
*/ 
void EmergencyState::is_working(void){
    if(elev->get_current_temp() <= elev->get_max_temp() && elev->get_load_weight() <= elev->get_max_load_weight()) 
    {
        Serial.println("ELEVATOR #" + String(elev->get_number()) + " HAS STABILIZED! OPERATIONS RESUMING!");
        this->run = true;
    }

    else{
        this->show_warning();
    }
}

/**
*  Returns a boolean indicating wether the current state can run. 
*
* @return A boolean, indicating whether the elevator can run or not.
*/ 
bool EmergencyState::can_run(void){
    return run;
}

/**
*  Receives a boolean and sets the state's current run attribute, denoting whether the state can be run. 
*
* @param set Sets the state's run attribute to the given boolean parameter.
*/ 
void EmergencyState::set_run(bool set){
    this->run = set;
}

/**
*  Identifies the current state's name. 
*
* @return The current state's name, as a String.
*/ 
String EmergencyState::current_state()
{
    return this->stateName;
}

/**
*  The state's destructor. The elevator is cleared out in the Finite State Machine.
*/ 
EmergencyState::~EmergencyState(){};

