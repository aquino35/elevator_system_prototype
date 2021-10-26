#include "EmergencyState.h"

void EmergencyState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
    Serial.println("ENTERING EMERGENCY STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + String(elev->get_number()) + " STABILIZES!");
}


void EmergencyState::unload(Elevator* elev, uint16_t weight){
    uint16_t toUnload = elev->get_load_weight() - weight;
    elev->set_load_weight(toUnload);
}

void EmergencyState::showWarning(Elevator* elev){
    Serial.println("CURRENTLY IN EMERGENCY STATE! NO COMMANDS WILL BE PROCESSED UNTIL THE ELEVATOR " + String(elev->get_number()) + " STABILIZES!");
    Serial.println("PARAMETERS MUST GO BACK TO THE MAXIMUM ALLOWED VALUES!");
    Serial.println("");
    Serial.println("PARAMETER DIFFERENCES:");
    Serial.println("-----------------------");

    if(elev->get_current_temp() > elev->get_max_temp()){
        Serial.println("TEMP IS " + String(elev->get_current_temp()) + "! MUST LOWER BY: " + String(elev->get_current_temp()-elev->get_max_temp()) + " DEGREES F!");
    }

    else if(elev->get_current_temp() <= elev->get_max_temp()){
        Serial.println("TEMP IS NORMAL!");
    }

    if(elev->get_capacity() > elev->get_max_load_weight()){
        Serial.println("CURRENT CAPACITY IS " + String(elev->get_current_temp()) + "! MUST LOWER BY: " + String(elev->get_capacity()-elev->get_max_load_weight()) + " POUNDS!");
    }

    else if(elev->get_capacity() <= elev->get_max_load_weight()){
        Serial.println("CAPACITY IS NORMAL!");
    }
    
}


void EmergencyState::isWorking(Elevator* elev){
    if(run) {Serial.println("ELEVATOR " + String(elev->get_number()) + " HAS STABILIZED! OPERATIONS RESUMING!");}

    else{
        showWarning(elev);
    }
}

bool EmergencyState::canRun(){
    return run;
}

void EmergencyState::setRun(bool set){
    run = set;
}



