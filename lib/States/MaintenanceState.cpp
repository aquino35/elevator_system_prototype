#include "MaintenanceState.h"

void MaintenanceState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
    Serial.println("ENTERING MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + String(elev->get_eid()) + " HAS BEEN FIXED!");
    Serial.println("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}

void MaintenanceState::showWarning(Elevator* elev){
    Serial.println("CURRENTLY IN MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR #" + String(elev->get_eid()) + " HAS BEEN FIXED!");
    Serial.println("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}


void MaintenanceState::isWorking(Elevator* elev){
    if(canRun) {Serial.println("ELEVATOR " + String(elev->get_eid()) + " HAS BEEN FIXED! OPERATIONS RESUMING!");}

    else{
        showWarning(elev);
    }
}

void MaintenanceState::check(String input, Elevator* elev){
    if(command.compareTo(input) == 0){
        setRun(true);
        isWorking(elev);
    }
}


bool MaintenanceState::canRun(){
    return canRun;
}

void MaintenanceState::setRun(bool set){
    canRun = set;
}

