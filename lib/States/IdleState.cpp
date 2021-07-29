#include "IdleState.h"

IdleState::IdleState(Elevator* elev){
    this->elev = elev;
    elev->setDoorStatus(true);
    elev-> setLightStatus(true);
}

void IdleState::load(uint16_t weight){
    uint16_t toAdd = elev->getLoadWeight() + weight;
    elev->setLoadWeight(toAdd);
}

void IdleState::unload(uint16_t weight){
    if(weight > elev->getMaxLoadWeight()) //goes into negative numbers
    {
        Serial.println("Can't unload more weight than is currently present!");
        return;
    }
    uint16_t toUnload = elev->getLoadWeight() - weight;
    elev->setLoadWeight(toUnload);
}

void IdleState::energySaving(){

    unsigned long seconds = 1000L;
    unsigned long minute = seconds * 60;
    delay(minute); // 1 minute delay
    elev-> setDoorStatus(false);
    if(elev->getLoadWeight()<0){
        elev->setLightStatus(false);
    }
}

