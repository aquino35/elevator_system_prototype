#include <InitialState.h>

InitialState::InitialState(Elevator* elev, uint8_t num, uint8_t floors)
{
    elev->setNumber(num);
    elev->setMaxFloor(floors);
}