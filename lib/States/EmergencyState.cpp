#include "EmergencyState.h"

//if the elevator's max weight or temp is exceeded, this state has to be activated
//it will go to idle state once the parameters are under their max values
//in this state the elevator will stop at the nearest floor, open the door and has its lights on
//it cannot receive any commands in this state, Any commads previously entered should be cleared. 

void EmergencyState::start(Elevator* elev){
    elev->setDoorStatus(true);
    elev->setLightStatus(true);
}

bool EmergencyState::emergency(Elevator* elev){
    
   if(elev->getLoadWeight() > elev->getMaxLoadWeight() || elev->getMaxTemp() > elev->getCurrentTemp()){
       return true;
   }   
   return false;
   
}

void EmergencyState::emergencyWorking(Elevator* elev){ //this all needs to be heavily reworked
    if (elev->getStateName().compareTo("Emergency") == 0){
        elev->getFloor();
        //and no input should be received
    }
    else{
       //return to idle state and inputs should be accepted again bc the elevator has the correct parameters
    }
    
}


