#include "MaintenanceState.h"

/**
* Contructor for the moving state. Initializes with the given elevator as a parameter.
*
* @param elevator The elevator being initialized in the current state.
*/
MaintenanceState::MaintenanceState(Elevator* elevator){
    this->elev = elevator;
}

/**
* Activating the maintenance state causes it to open the elevator's doors and turn the lights on, 
* so the techninician can begin inspecting it. Prompts the maintenance state's warning.
*/ 
void MaintenanceState::start(void){
    elev->open();
    elev->turn_lights_on();
    this->show_warning();
}

/**
* Displays a warning indicating that the elevator is under mantenance.
*/ 
void MaintenanceState::show_warning(void){
    Serial.println("CURRENTLY IN MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL ELEVATOR #" + String(elev->get_number()) + " HAS BEEN FIXED!" );
    Serial.println("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}

/**
* Verifies whether the elevator is working once again by checking the state's run attribute. If it isn't working yet, displays a warning.
*/ 
void MaintenanceState::is_working(void){
    if(run) {
        Serial.println("ELEVATOR " + String(elev->get_number()) + " HAS BEEN FIXED! OPERATIONS RESUMING!");
    }

    else{
        this->show_warning();
    }
}

/**
* Given an input command, verifies whether its the one required to resume the elevator's operations. If so, 
* allows it to run.
* 
* @param input The input command, as a String, which allows it to resume operations.
*/ 
void MaintenanceState::check(String input){
    if(command.compareTo(input) == 0){
        this->set_run(true);
        this->is_working();
    }
}

/**
* Returns a boolean indicating wether the current state can run. 
*
* @return A boolean, indicating whether the elevator can run or not.
*/ 
bool MaintenanceState::can_run(void){
    return run;
}

/**
* Receives a boolean and sets the state's current run attribute, denoting whether the state can be run. 
*
* @param set Sets the state's run attribute to the given boolean parameter.
*/ 
void MaintenanceState::set_run(bool set){
    this->run = set;
}

/**
* Identifies the current state's name. 
*
* @return The current state's name, as a String.
*/ 
String MaintenanceState::current_state()
{
    return this->stateName;
}

/**
* The state's destructor. The elevator is cleared out in the Finite State Machine.
*/ 
MaintenanceState::~MaintenanceState(){};
