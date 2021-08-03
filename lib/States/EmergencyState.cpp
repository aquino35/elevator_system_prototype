#include "EmergencyState.h"

//if the elevator's max weight or temp is exceeded, this state has to be activated
//it will go to idle state once the parameters are under their max values
//in this state the elevator will stop at the nearest floor, open the door and has its lights on
//it cannot receive any commands in this state, Any commads previously entered should be cleared. 

bool EmergencyState::Emergency(Elevator* elev){
    
   if(getLoadWeight() > getMaxLoadWeight() || getMaxTemp() > getCurrentTemp()){
       return true;
   }   
   
}

void EmergencyState::EmergencyWorking(Elevator* elev){
    if (Emergency() == true){
        this->elev = elev;
        elev->setDoorStatus(true);
        elev->setLightStatus(true);
        elev ->getFloor();
        //and no input should be received
    }
    else{
       //return to idle state and inputs should be accepted again bc the elevator has the correct parameters
    }
    
}


