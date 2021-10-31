#include "MaintenanceState.h"

MaintenanceState::MaintenanceState(Elevator* elevator){
    this->elev = elevator;
}

void MaintenanceState::start(){
    elev->set_door_status(true);
    elev->set_light_status(true);
    Serial.println("ENTERING MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + String(elev->get_number()) + " HAS BEEN FIXED!");
    Serial.println("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}

void MaintenanceState::showWarning(){
    Serial.println("CURRENTLY IN MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR #" + String(elev->get_number()) + " HAS BEEN FIXED!");
    Serial.println("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}


void MaintenanceState::isWorking(){
    if(run) {Serial.println("ELEVATOR " + String(elev->get_number()) + " HAS BEEN FIXED! OPERATIONS RESUMING!");}

    else{
        showWarning();
    }
}

void MaintenanceState::check(String input){
    if(command.compareTo(input) == 0){
        setRun(true);
        isWorking();
    }
}


bool MaintenanceState::canRun(){
    return run;
}

void MaintenanceState::setRun(bool set){
    run = set;
}

