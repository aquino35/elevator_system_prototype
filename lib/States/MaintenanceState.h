#pragma once
#include "Elevator.h"
#include "State.h"

class MaintenanceState : public State{
    
    private:
        String stateName = "Maintenance";
        bool run = false;
        String command = "M"; //placeholder
    
    public: 
        void start(Elevator* elev);
        bool canRun(); 
        void setRun(bool set);
        
        void showWarning(Elevator* elev); //show a warning every time a user tries to us an elevator in maintenance state
        void isWorking(Elevator* elev); //show a warning every time a user tries to us an elevator in maintenance state
        void check(String input, Elevator* elev); //checks if the current command entered unlocks maintanence
        String currentState(){return this->stateName;}
        
};