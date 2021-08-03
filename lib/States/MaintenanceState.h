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

        bool WorkMaintenance();
        MaintenanceState(boolean Option);
        
        String currentState(){return this->stateName;}

        
}