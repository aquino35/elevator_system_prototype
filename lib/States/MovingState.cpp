#include "MovingState.h"

//MISSING MOVING STATE FUNCTIONALITIES

MovingState::MovingState(Elevator* elevator){
    this->elev = elevator;
}

void MovingState::start(){
    elev->set_door_status(false);
    elev->set_light_status(true);
}

uint8_t MovingState::get_nearest_floor()
{
    Set* stoppingFloors = elev->get_stopping_floors();

    if(stoppingFloors->size() < 1){
        Serial.print("ELEV #" + String(elev->get_number()) + " CAN'T CHANGE FLOORS!");
        return -1; //SWITCH TO IDLE
    }

    if(stoppingFloors->size() == 1) return stoppingFloors->get(0); 

    uint8_t nearestDifference = 40; 
    uint8_t goTo;
    
    for(int i = 0; i < stoppingFloors->size(); i++) //get the nearest floor 
    {
        uint8_t currentStopping = stoppingFloors->get(i);
        if(abs(currentStopping - elev->get_floor()) <= nearestDifference && currentStopping != elev->get_floor()){
            nearestDifference = abs(currentStopping - elev->get_floor());
            goTo = currentStopping;
        }
    }
    return goTo;
}

void MovingState::set_direction()
{
    uint8_t floor = get_nearest_floor();

    if(floor == -1){
        Serial.println("ELEVATOR #" + String(elev->get_number()) + " HAS NO REQUESTED FLOORS!");
        run = false;
        return;
    }


    if(floor <= elev->get_max_floor()){ 
        this->toFloor = floor;

        if(elev->get_floor() < this->toFloor){ //direction lock
            direction_lock = UP;
        }

        else if (elev->get_floor() > this->toFloor){
            direction_lock = DOWN;
        }

        Serial.println("ELEVATOR " + String(elev->get_number()) + " EN ROUTE TO FLOOR# " + String(toFloor) + "!");
        run = true;
    }

    else{ //transition to idle state somehow
        Serial.println("FLOOR #" + String(floor) + " DOESNT EXIST!");
        run = false;
    }

}


void MovingState::moving_timer()
{
    begin = clock();
    time_spent = (double)(clock() - begin);

    Serial.print("ELEVATOR #" + String(elev->get_number()) + " TRANSITIONING TO ANOTHER FLOOR!");

    while(time_spent != 3000.0){ //3 second timer
        time_spent = (double)(clock() - begin);
    }
}

void MovingState::move_nearest() //moves to the nearest floor in the building
{
    uint8_t currentFloor = elev->get_floor(); 
    
    //will be called after emergency state so we don't care about whether we can run it or not
    
    if(currentFloor + 1 != elev->get_max_floor()){ //direction lock
        currentFloor++;
    }

    else{
        currentFloor--;
    }
        
    moving_timer();
    elev->set_floor(currentFloor); 
    Serial.println("ELEVATOR #" + String(elev->get_number()) + " CURRENTLY ON FLOOR #" + String(toFloor) + "!");
    
}

void MovingState::move(){ //Set implemented with Linked List, moves on floor at a time
    uint8_t currentFloor = elev->get_floor();
    Set* stoppingFloors = elev->get_stopping_floors();
    

    if(run && direction_lock != NULL){
        if(direction_lock == UP){ //direction lock
            currentFloor++;
        }

        else if (direction_lock == DOWN){
            currentFloor--;
        }
        
        //DONT USE DELAY
        moving_timer();
        elev->set_floor(currentFloor); 
        Serial.println("ELEVATOR #" + String(elev->get_number()) + " CURRENTLY ON FLOOR # " + String(toFloor) + "!");

        if(stoppingFloors->contains(currentFloor)){
            Serial.println("ELEVATOR #" + String(elev->get_number()) + " CURRENTLY LEAVING AND PICKING PEOPLE ON FLOOR #" + String(toFloor) + "!");
            stoppingFloors->remove(currentFloor);
            stopped = true;
        }
        else stopped = false;
    }
}

bool MovingState::canMove(){
    Set* stoppingFloors = elev->get_stopping_floors();
    return stoppingFloors->size() > 0;
}

bool MovingState::should_switch_direction() //whether we should change direction lock
{ 
    Set* stoppingFloors = elev->get_stopping_floors();
    bool shouldChange = true;

    for(int i = 0; i < stoppingFloors->size(); i++) //get the nearest floor 
    {
        uint8_t otherFloors = stoppingFloors->get(i);
        if(direction_lock == UP && otherFloors > elev->get_floor()){ //more floors up
            shouldChange = false;            
        }

        else if(direction_lock == DOWN && otherFloors < elev->get_floor()){ //more floors down
            shouldChange = false;            
        }

    }
    return shouldChange;
}

bool MovingState::made_stop(){
    return stopped;
}

bool MovingState::canRun(){
    return run;
}

void MovingState::setRun(bool set){
    run = set;
}

