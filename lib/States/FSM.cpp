#include "FSM.h"

FSM::FSM(Elevator* elevator)
{
    this->elev = elevator;
    initial_state = new InitialState(elev); 
    idle_state = new IdleState(elev);
    moving_state = new MovingState(elev);
    emergency_state = new EmergencyState(elev); 
    maintenance_state = new MaintenanceState(elev);
}

void FSM::setup(void)
{
    initial_state->start(); 
    idle_state->start();
    currentStateName = idle_state->currentState();
}
 
//should go inside some mainloop
void FSM::energyUpdate(void)
{
    if(currentStateName.compareTo("Idle") == 0 && !toggle){ 
        begin = clock();
        time_spent = (double)(clock() - begin);

        while(time_spent != 15000.0){ //15 second timer
            time_spent = (double)(clock() - begin);
        }

        idle_state->energySaving();
    }
}

void FSM::run(uint8_t command) //manages transitions
{
    //if you havent set a state or you're in maintenanace and haven't input the command to unlock maintenance
    if(currentStateName.compareTo("") == 0 || (currentStateName.compareTo("Maintenance") == 0 && command != 13)){ //cant run
        Serial.print("CAN'T RUN ELEVATOR #" + String(elev->get_number()) + "! PLEASE FIX ISSUES");
        command = 10; //set to maintenance state
    }

    switch(command){
        case 7: //load people (300 lbs)
            if(currentStateName.compareTo("Idle") == 0){
                idle_state->start();
                idle_state->load(300);
                toggle = true; //wont go into reset, means elevator was activated, reset timer

                if(elev->get_load_weight() > elev->get_max_load_weight()){ //EMERGENCY STATE
                    emergency_state->start();
                    currentStateName = emergency_state->currentState();
                    emergency_state->showWarning();

                    moving_state->start();
                    moving_state->move_nearest();
                    emergency_state->unload(elev->get_load_weight()); //empty elevator
                    emergency_state->isWorking();
                    
                    idle_state->start();
                    currentStateName = idle_state->currentState();
                    toggle = false;
                    break;
                }

            }

            else {Serial.print("Inacessible from the current state: " + currentStateName);}
            currentStateName = idle_state->currentState();
            toggle = false;
            break;

        case 8: //unload people (300 lbs)
            if(currentStateName.compareTo("Idle") == 0){
                idle_state->start();
                idle_state->unload(300);
                toggle = true; //wont go into reset, means elevator was activated
            }

            else {Serial.print("Inacessible from the current state: " + currentStateName);}
            currentStateName = idle_state->currentState();
            toggle = false;
            break;

        case 9: //moving
            if(currentStateName.compareTo("Idle") == 0){
                currentStateName = moving_state->currentState();
                moving_state->start();
                moving_state->set_direction(); //direction lock
                
                while(moving_state->canMove()){
                    moving_state->move();
                    //loading and unloading
                    if(moving_state->made_stop()){
                        idle_state->start();
                        idle_state->load(300); //not sure when to pick or leave people off while moving or how much 
                        idle_state->unload(300);
                    }

                    if(moving_state->should_switch_direction()){ //switch direction lock 
                        moving_state->set_direction();
                    }
                }
            }

            idle_state->start();
            currentStateName = idle_state->currentState();
            toggle = false;
            break;

        case 10:
            currentStateName = maintenance_state->currentState();
            maintenance_state->start();
            maintenance_state->showWarning();
            break;

        case 13: //unlock maintenance state
            maintenance_state->check("M");
            maintenance_state->isWorking();
            idle_state->start();
            currentStateName = idle_state->currentState();
            toggle = false;
            break;
    }
}

FSM::~FSM()
{
    delete elev;
    delete initial_state;
    delete idle_state;
    delete moving_state;
    delete emergency_state;
    delete maintenance_state;
}