#include "IdleState.h"

void IdleState::start(Elevator* elev){
    elev->setDoorStatus(true);
    elev->setLightStatus(true);
}

void IdleState::load(Elevator* elev, uint16_t weight){
    uint16_t toAdd = elev->getLoadWeight() + weight;
    elev->setLoadWeight(toAdd);
}

void IdleState::unload(Elevator* elev, uint16_t weight){
    if(weight > elev->getMaxLoadWeight()){ //goes into negative numbers
        Serial.println("Can't unload more weight than is currently present!");
        return;
    }
    uint16_t toUnload = elev->getLoadWeight() - weight;
    elev->setLoadWeight(toUnload);
}

