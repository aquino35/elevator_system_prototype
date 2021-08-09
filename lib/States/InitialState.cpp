#include "InitialState.h"

void InitialState::start(Elevator* elev)
{
    elev->setLoadWeight(0);
    elev->setDoorStatus(false);
    elev->setLightStatus(true);
    elev->setFloor(1);
    elev->setCurrentTemp(60);
}