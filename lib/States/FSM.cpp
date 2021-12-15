#include "FSM.h"

/**
* FSM Constructor. Initializes all the states with the given elevator as a parameter.
*
* @param elevator The elevator object the FSM will manage.
*/
FSM::FSM(Elevator* elevator)
{
    this->elev = elevator;
    initialState = new InitialState(elev); 
    idleState = new IdleState(elev);
    movingState = new MovingState(elev);
    emergencyState = new EmergencyState(elev); 
    maintenanceState = new MaintenanceState(elev);

    server = new SystemServer();
    server->setup();
    people_in = new Set();
}

/**
* Starts the FSM by initializing the elevator. Current state is set to idle state since
* the the run() method assumes this.
*/ 
void FSM::setup(void) //dont initialize idle start here
{
    initialState->start(); 
    currState = IDLE_STATE;
}

/**
* Causes an unused elevator, after a period of 15 seconds, to shut its doors and turn the lights off
* to conserve energy. 
*/  
void FSM::energy_update(void) //should go in some mainloop
{
    if(currState == IDLE_STATE && elev->get_load_weight() == 0){ 
        begin = clock();
        timeSpent = (double)(clock() - begin);

        while(true){ //15 second timer
            timeSpent = (double)(clock() - begin);
            if(timeSpent >= 15000.00) return;
        }

        idleState->energy_saving();
    }
    message = ENERGY_SAVING;
    update_server();
}

/**
* Toggles the emergency state, a condition which could occur at any point
* people are being loaded. Moves to the nearest floor and stabilizes the 
* elevator's parameters.
*/ 
void FSM::emergency_toggle()
{
    emergencyState->start();
    currState = EMERGENCY_STATE;

    movingState->start();
    movingState->move_nearest();
    emergencyState->unload(elev->get_load_weight()); //empty elevator
    people_in->clear();
    elev->set_current_temp(65);
    emergencyState->is_working();

    idleState->start();
    currState = IDLE_STATE;
    toggle = false;

    message = EMERGENCY;
    update_server();

}

/**
* Moves the elevator to the requested floors, one floor at a time,
* until the set containing the requested floors is empty. Goes into the emergency 
* state if more people are loaded than the elevator can handle or if it gets too hot.
*
*/ 
void FSM::moving_loop()
{
    movingState->start();
    movingState->set_direction(); //direction lock
                
    while(movingState->can_move()){
        movingState->move();

        message = MOVED;
        update_server();

        //loading and unloading
        if(movingState->made_stop()){
            load_in();
            elev->close();

            message = LOADED;
            update_server();


            if(elev->get_load_weight() > elev->get_max_load_weight() || elev->get_current_temp() > elev->get_max_temp()){
                this->emergency_toggle();
                return; //prevents idle state from being initialized twice and from the elevator moving immediately after
            }
        }

        if(movingState->should_switch_direction()){ //switch direction lock 
            movingState->set_direction();
            message = CHANGED_DIRECTION;
            update_server();

        }
    }

    idleState->start();
    currState = IDLE_STATE;
    toggle = false;
    message = IDLE;
    update_server();

}

/**
* If a state is inaccesable from another state, determines which is the current state and prints
* an error message to the terminal.
*/ 
void FSM::warning()
{
    String state; 
    switch(currState){
        case 1:
            state = initialState->current_state();
            message = INITIAL;
            break;
            
        case 2:
            state = idleState->current_state();
            message = IDLE;
            break;

        case 3:
            state = movingState->current_state();
            message = MOVED;
            break; 

        case 4:
            state = emergencyState->current_state();
            message = EMERGENCY;
            break;

        case 5:
            state = maintenanceState->current_state();
            message = MAINTENANCE;
            break;

        default: 
            state = "no set state";
            message = ERROR;
            break;

    }

    Serial.println("CAN'T RUN ELEVATOR #" + String(elev->get_number()) + " FROM THE CURRENT STATE: " + state );
    update_server();

}


void FSM::update_server(){
    server->set_eid(elev->get_number());
    server->set_door_status(elev->is_door_open());
    server->set_light_status(elev->is_light_on());
    server->set_floor(elev->get_floor());
    server->set_temp(elev->get_current_temp());
    server->set_load(elev->get_load_weight());
    server->set_person_counter(elev->get_people()); 
    server->serial_service_tx(server->get_queue(), (uint8_t) 14);
    server->set_msg_to_usesr(message);
}

void FSM::load_in(){
    person* human = elev->load_people_in();
    people_in->add(human->get_person());
    idleState->load(human->get_weight());
    elev->set_current_temp(elev->get_current_temp() + human->get_temp());
}

void FSM::unload_person(){
    uint8_t person_type = people_in->remove(0);
    uint8_t temp;
    idleState->unload(person_type); //remnove people with their ID
    switch(person_type){
        case 1:
            temp = 5;
            break;

        case 2:
            temp = 3;
            break;

        case 3:
            temp = 4;
            break;
    }
    elev->set_current_temp(elev->get_current_temp() - temp);

}

/**
* Given a command, mapped to numerical values, performs one of the following actions: 
*   -Load: Loads the given amount of people onto the elevator. Can only be accessed from the idle state.
*          If the elevator's parameters exceed the permitted ones, goes into emergency state.
*
*   -Unload: Unloads the given amount of people onto the elevator. Can only be accessed from the idle state.
*
*   -Move: Moves the elevator to the requested floors. If the elevator's parameters exceed the permitted ones, goes into emergency state.
*          Can only be accessed from the idle state.
*
*   -Maintenance: If the maintenance command is entered, sets the elevator into maintenance state. Accessible from any state.
*                 Can only be disactivated with a special input command. Refer to the elevator system administrator.

*   -Fix Maintenance: If the elevator was down for maintenance and the command is the correct one, stops the downtime and resumes the elevator's operations.
*
* @param command The numerical command to be executed. Prints a warning to the command line if an invalid command is attempted.
*/ 
void FSM::run(int command) //manages transitions
{
    switch(command){
        case LOAD_COMMAND: //load people (300 lbs)
            if(currState == IDLE_STATE){
                idleState->start();
                toggle = true; //wont go into reset, means elevator was activated, reset timer
                load_in();
                if(elev->get_load_weight() > elev->get_max_load_weight() || elev->get_current_temp() > elev->get_max_temp()){ //EMERGENCY STATE
                    this->emergency_toggle();
                    break;
                }

            }

            else warning();
            toggle = false;
            message = LOADED;
            update_server();
            break;

        case UNLOAD_COMMAND: //unload people (300 lbs)
            if(currState == IDLE_STATE){
                idleState->start();
                unload_person();
                toggle = true; //wont go into reset, means elevator was activated
            }

            else warning();
            toggle = false;
            message = UNLOADED;
            update_server();
            break;

        case MOVE_COMMAND: //moving
            if(currState ==  IDLE_STATE){
                currState = MOVING_STATE;
                this->moving_loop();
            }

            else warning();
            message = MOVED;
            update_server();
            break;

        case MAINTENANCE_COMMAND: //lock maintenance state
            currState = MAINTENANCE_STATE;
            maintenanceState->start();
            message = MAINTENANCE;
            update_server();
            break;

        case FIX_MAINTENANCE_COMMAND: //unlock maintenance state
            if(currState == MAINTENANCE_STATE){
                maintenanceState->check("C");
                idleState->start();
                currState = IDLE_STATE;
                toggle = false;
            }

            else warning();
            message = IDLE;
            update_server();
            break;

        default: 
            Serial.println("Command #" + String(command) + " isn't a registered command! Please enter a valid command." );
            message = ERROR;
            update_server();
            break;
    }
}

/**
* The Finite State Machine destructor. Terminates the elevator and all of the dynamically allocated space.
*/ 
FSM::~FSM(void)
{
    delete elev;
    delete initialState;
    delete idleState;
    delete movingState;
    delete emergencyState;
    delete maintenanceState;
    delete server;
}