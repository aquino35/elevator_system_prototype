#include <NormalState.h>

NormalState::NormalState(Elevator* elev, uint8_t num, uint8_t floors)
{
    elev->setNumber(num);
    elev->setMaxFloor(floors);
}