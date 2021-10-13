#include "MaintenanceState.h"

void MaintenanceState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
    Serial.print("ENTERING MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + elev->get_eid() + " HAS BEEN FIXED!");
    Serial.print("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}

void MaintenanceState::showWarning(){
    Serial.print("ENTERING MAINTENANCE STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + elev->get_eid() + " HAS BEEN FIXED!");
    Serial.print("ENTER THE SPECIAL INPUT COMMAND IN ORDER TO COMPLETE MAINTENANCE!");
}

bool MaintenanceState::canRun(){
    return canStart;
}

void MaintenanceState::setRun(bool set){
    canRun = set;
}

