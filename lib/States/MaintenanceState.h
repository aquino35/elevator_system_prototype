#pragma once
#include "State.h"
#include "Elevator.h"

// //Special input that indicates this state
// //all prev commands must be cleared and no other command will be processed
// //the only command it must react to is the one that turns the state off and moves to idle state back again. 

// //if "nombredelavariabledelbotondemaintenance" true, then activate this state.
class MaintenanceState{
    private:
        boolean Option; //optionOn must be equal to an input in the main file
        String stateName = "Maintenance";
    
    public: 
        bool WorkMaintenance(){
            //if opcion de maintenance en el main se elige
            return Option = true;
            //if apagado
            return Option = false;
        }

        MaintenanceState(boolean OptionOn, boolean OptionOff){ 
           if Option = true;
           //que no se puedan recibir comandos
        
           else:
            OptionOff == true:
        }

        String currentState(){return this->stateName;}

        
}