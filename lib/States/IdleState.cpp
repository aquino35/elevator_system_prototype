#include "IdleState.h"

IdleState::IdleState(Elevator* elev){
    this->elev = elev;
    elev->setDoorStatus(true);
    elev->setLightStatus(true);
    this->start = time(0);
}

void IdleState::load(uint16_t weight){
    this->start = time(0); //reset time when executing commands
    uint16_t toAdd = elev->getLoadWeight() + weight;
    elev->setLoadWeight(toAdd);
}

void IdleState::unload(uint16_t weight){
    this->start = time(0);
    if(weight > elev->getMaxLoadWeight()) //goes into negative numbers
    {
        Serial.println("Can't unload more weight than is currently present!");
        return;
    }
    uint16_t toUnload = elev->getLoadWeight() - weight;
    elev->setLoadWeight(toUnload);
}

void IdleState::tick(){ //only testing with 15 seconds for now
    uint16_t seconds_since_start = difftime(time(0), start);

    if(seconds_since_start == 15 && elev->getLoadWeight() == 0){ //power saving mode
        elev->setDoorStatus(false);
        elev->setLightStatus(false);

        String elevNum = String(elev->getNumber());
        Serial.println("Elevator " + elevNum + " has entered power saving mode.");
    }

    if(seconds_since_start > 15) //dont do anything during power saving mode
        return;

}

// void IdleState::energySaving(){

//     unsigned long seconds = 1000L;
//     unsigned long minute = seconds * 60;
//     delay(minute); // 1 minute delay
//     elev-> setDoorStatus(false);
//     if(elev->getLoadWeight()<0){
//         elev->setLightStatus(false);
//     }
// }

