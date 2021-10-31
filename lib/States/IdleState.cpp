#include "IdleState.h"

//MISSING MOVING STATE FUNCTIONALITIES

IdleState::IdleState(Elevator* elevator){
    this->elev = elevator;
}

void IdleState::start(){
    elev->set_door_status(true);
    elev->set_light_status(true);
    Serial.println("ENTERING IDLE STATE!");

}

void IdleState::load(uint16_t weight){
    uint16_t toAdd = elev->get_load_weight() + weight;
    elev->set_load_weight(toAdd);
}

void IdleState::unload(uint16_t weight){
    if(weight > elev->get_max_load_weight()){ //goes into negative numbers
        Serial.println("Can't unload more weight than is currently present!");
        return;
    }
    uint16_t toUnload = elev->get_load_weight() - weight;
    elev->set_load_weight(toUnload);
}

void IdleState::energySaving(){
    Serial.println("ELEVATOR " + String(elev->get_number()) + " HAS BEEN UNUSED FOR 30 SECONDS, ENTERING ENERGY SAVING MODE!");
    elev->set_door_status(false);
    if(elev->get_capacity() == 0){
        elev->set_light_status(false);
    }
}

bool IdleState::canRun(){
    return run;
}

void IdleState::setRun(bool set){
    run = set;
}

