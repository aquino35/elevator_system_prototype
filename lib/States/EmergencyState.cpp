#include "EmergencyState.h"

//if the elevator's max weight or temp is exceeded, this state has to be activated
//it will go to idle state once the parameters are under their max values
//in this state the elevator will stop at the nearest floor, open the door and has its lights on
//it cannot receive any commands in this state, Any commads previously entered should be cleared. 

void EmergencyState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
    Serial.print("ENTERING EMERGENCY STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + elev->get_eid() + " HAS BEEN FIXED!");
}


void EmergencyState::showWarning(){
    Serial.print("ENTERING EMERGENCY STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + elev->get_eid() + " HAS BEEN FIXED!");
}

bool EmergencyState::canRun(){
    return canRun;
}

void EmergencyState::setRun(bool set){
    canRun = set;
}



