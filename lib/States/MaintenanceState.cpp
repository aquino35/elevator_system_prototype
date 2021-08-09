#include "MaintenanceState.h"

void MaintenanceState::start(Elevator* elev){
    elev->setDoorStatus(true);
    elev->setLightStatus(true);
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
