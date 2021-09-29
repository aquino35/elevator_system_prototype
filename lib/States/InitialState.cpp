#include "InitialState.h"

void InitialState::start(Elevator* elev)
{
    elev->set_load_weight(0);
    elev->set_door_status(false);
    elev->set_light_status(true);
    elev->set_floor(1);
    elev->set_current_temp(60);
}