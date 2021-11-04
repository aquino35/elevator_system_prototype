#pragma once
#include "State.h"

class MaintenanceState : public State{
    
    private:
        String stateName = "Maintenance";
        bool run = false;
        String command = "M"; //placeholder
        Elevator* elev;
    
    public: 
        MaintenanceState(Elevator* elevator);
        void start();
        bool canRun(); 
        void setRun(bool set);
        
        void showWarning(); //show a warning every time a user tries to us an elevator in maintenance state
        void isWorking(); //show a warning every time a user tries to us an elevator in maintenance state
        void check(String input); //checks if the current command entered unlocks maintanence
        String currentState(){return this->stateName;}
        ~MaintenanceState(){};
        
};