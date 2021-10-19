#include "InitialState.h"

void InitialState::start(Elevator* elev)
{
    elev->set_load_weight(0);
    elev->set_door_status(false);
    elev->set_light_status(true);
    elev->set_floor(1);
    elev->set_current_temp(60);
    Serial.println(String(elev->get_eid()) + " INITIALIZED!");
}

bool InitialState::canRun(){
    return canRun;
}

void InitialState::setRun(bool set){
    canRun = set;
}
