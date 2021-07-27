#include "IdleState.h"

IdleState::IdleState(Elevator* elev){
    this->elev = elev;
}

void IdleState::load(uint16_t weight){
    uint16_t toAdd = elev->getLoadWeight() + weight;
    elev->setLoadWeight(toAdd);
}

void IdleState::unload(uint16_t weight){
    if(weight > elev->getMaxLoadWeight()) //goes into negative numbers
    {
        Serial.print("Can't unload more weight than is currently present!");
        return;
    }
    uint16_t toUnload = elev->getLoadWeight() - weight;
    elev->setLoadWeight(toUnload);
}

