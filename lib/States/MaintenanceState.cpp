#include "MaintenanceState.h"

void MaintenanceState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
}

bool MaintenanceState::workMaintenance(){
    //if opcion de maintenance en el main se elige
    return Option = true; //porque option = input del main menu cuando se elija
    //else{
    return Option = false;
    //}
}

void MaintenanceState::maintenanceState(boolean Option){ 
    if (Option == true){
        //que no se puedan recibir comandos and prev ones must be cleared 
    }
    else{
        //with an exit option in the interface when maintenance is called, if called, exit this state
    }
}

bool MaintenanceState::canRun(){
    return canStart;
}

void MaintenanceState::setRun(bool set){
    canRun = set;
}

