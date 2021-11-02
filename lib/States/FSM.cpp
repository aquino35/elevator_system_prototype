#include "FSM.h"

FSM::FSM(Elevator* elevator)
{
    this->elev = elevator;
    State* state[5] = {new InitialState(elev), new IdleState(elev), new MovingState(elev), new EmergencyState(elev), new MaintenanceState(elev)};

    for(int i = 0; i < 5; i++){ //cant figure a way to initilaize states array 
        states[i] = state[i];
    }

}

void FSM::setup(void)
{
    states[INITIAL_OFFSET]->start(); 
    states[IDLE_OFFSET]->start();
    currentState = states[IDLE_OFFSET]->currentState();
}

void FSM::run(uint8_t command) //manages transitions
{
    if(current_state != NULL && !current_state->canRun()){ //cant run
        Serial.print("CAN'T RUN ELEVATOR # " + String(elev->get_number()) + "! PLEASE FIX ISSUES");
        command = 8; //set to maintenance state
    }

    switch(command){

        case 7: //load people  (300 lbs)
            if(currentState.compareTo("Idle") || currentState.compareTo("Moving")){
                IdleState* current_state = dynamic_cast<IdleState*>(states[IDLE_OFFSET]);
                current_state->load(300);

                if(elev->get_load_weight() >= elev->get_max_load_weight()){ //EMERGENCY STATE
                    EmergencyState* current_state = dynamic_cast<EmergencyState*>(states[EMERGENCY_OFFSET]);
                    currentState = states[EMERGENCY_OFFSET]->currentState();
                    current_state->showWarning();

                    MovingState* current_state = dynamic_cast<MovingState*>(states[MOVING_OFFSET]);
                    // if(elev->get_floor() +1 != elev->get_max_floor()){
                    //     current_state->setup(elev->get_floor() +1);
                    // }

                    break;
                }

                if(currentState.compareTo("Moving")){ //change back to moving after loading
                    begin = clock();
                    time_spent = (double)(clock() - begin);

                    Serial.print(String(elev->get_number()) + " TRANSITIONING TO ANOTHER FLOOR!");

                    while(time_spent != 3000.0){ //3 second timer
                        time_spent = (double)(clock() - begin);
                    }
                    
                    MovingState* current_state = dynamic_cast<MovingState*>(states[MOVING_OFFSET]);
                    current_state->moving();
                    break; //wont change current state to idle state

                }

            }

            else {Serial.print("Inacessible from the current state: " + currentState);}
            currentState = states[IDLE_OFFSET]->currentState();

            break;

        case 8: //unload people (300 lbs)
            if(currentState.compareTo("Idle") || currentState.compareTo("Moving")){
                IdleState* current_state = dynamic_cast<IdleState*>(states[IDLE_OFFSET]);
                current_state->unload(300);

                if(currentState.compareTo("Moving")){ //change back to moving after loadingd

                    begin = clock();
                    time_spent = (double)(clock() - begin);

                    Serial.print(String(elev->get_number()) + " TRANSITIONING TO ANOTHER FLOOR!");

                    while(time_spent != 3000.0){ //3 second timer
                        time_spent = (double)(clock() - begin);
                    }
                    
                    MovingState* current_state = dynamic_cast<MovingState*>(states[MOVING_OFFSET]);
                    current_state->moving();
                    break; //wont change current state to idle state

                }

            }

            else {Serial.print("Inacessible from the current state: " + currentState);}
            currentState = states[IDLE_OFFSET]->currentState();

            break;

        case 9: 
            if(currentState.compareTo("Idle")){

            }

            break;

        case 10: //maintenance command
            break;
    }
}

FSM::~FSM()
{
    delete elev;
    delete states;
}