#pragma once
#include "Elevator.h"

// //Special input that indicates this state
// //all prev commands must be cleared and no other command will be processed
// //the only command it must react to is the one that turns the state off and moves to idle state back again. 

// //if "nombredelavariabledelbotondemaintenance" true, then activate this state.
class MaintenanceState{
    
    private:
        bool Option; //optionOn must be equal to an input in the main file
        String stateName = "Maintenance";
        bool canRun = false;
    
    public: 
        void start(Elevator* elev);
        bool canRun(); 
        void setRun(bool set);
        
        void showWarning(); //show a warning every time a user tries to us an elevator in maintenance state
        String currentState(){return this->stateName;}
        
};