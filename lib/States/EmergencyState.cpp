#include "EmergencyState.h"

//if the elevator's max weight or temp is exceeded, this state has to be activated
//it will go to idle state once the parameters are under their max values
//in this state the elevator will stop at the nearest floor, open the door and has its lights on
//it cannot receive any commands in this state, Any commads previously entered should be cleared. 

void EmergencyState::start(Elevator* elev){
    elev->set_door_status(true);
    elev->set_light_status(true);
}

bool EmergencyState::emergency(Elevator* elev){
    
   if(elev->get_load_weight() > elev->get_max_load_weight() || elev->get_max_temp() > elev->get_current_temp()){
       return true;
   }   
   return false;
   
}

void EmergencyState::emergencyWorking(Elevator* elev){ //this all needs to be heavily reworked
    if (elev->get_state_name().compareTo("Emergency") == 0){
        elev->get_floor();
        //and no input should be received
    }
    else{
       //return to idle state and inputs should be accepted again bc the elevator has the correct parameters
    }
    
}


