#include "Moving.h"

//MISSING MOVING STATE FUNCTIONALITIES

void IdleState::start(Elevator* elev, uint8_t floor){
    elev->set_door_status(false);
    elev->set_light_status(true);
    this->toFloor = floor;
    Serial.println("ELEVATOR EN ROUTE TO " + String(toFloor) + "!");
}

bool IdleState::canRun(){
    return canRun;
}

void IdleState::setRun(bool set){
    canRun = set;
}

