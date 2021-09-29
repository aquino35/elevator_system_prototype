#include "IdleState.h"

void IdleState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
}

void IdleState::load(Elevator* elev, uint16_t weight){
    uint16_t toAdd = elev->get_load_weight() + weight;
    elev->set_load_weight(toAdd);
}

void IdleState::unload(Elevator* elev, uint16_t weight){
    if(weight > elev->get_max_load_weight()){ //goes into negative numbers
        Serial.println("Can't unload more weight than is currently present!");
        return;
    }
    uint16_t toUnload = elev->get_load_weight() - weight;
    elev->set_load_weight(toUnload);
}

