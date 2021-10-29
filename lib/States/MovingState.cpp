#include "MovingState.h"

//MISSING MOVING STATE FUNCTIONALITIES

void MovingState::start(Elevator* elev){
    elev->set_door_status(false);
    elev->set_light_status(true);
}

void MovingState::setup(Elevator* elev, uint8_t floor)
{
    if(floor == elev->get_floor()){ //transition to idle state somehow
        Serial.println("ELEVATOR " + String(elev->get_number()) + " IS ON THIS SAME FLOOR!");
        run = false;
        return;
    }

    else if(floor <= elev->get_max_floor()){ 
        this->toFloor = floor;

        if(elev->get_floor() < this->toFloor){ //direction lock
            direction = UP;
        }

        else if (elev->get_floor() > this->toFloor){
            direction = DOWN;
        }

        Serial.println("ELEVATOR " + String(elev->get_number()) + " EN ROUTE TO FLOOR# " + String(toFloor) + "!");
        run = true;
    }

    else{ //transition to idle state somehow
        Serial.println("FLOOR # " + String(floor) + " DOESNT EXIST!");
        run = false;
        return;
    }

}

void MovingState::moving(Elevator* elev, Set* stoppingFloors){ //Set implemented with Linked List
    uint8_t currentFloor = elev->get_floor();

    if(run){
        while (currentFloor != this->toFloor) 
        {
            if(direction == UP){ //direction lock
                currentFloor++;
            }

            else if (direction == DOWN){
                currentFloor--;
            }
        
            //DONT USE DELAY, transfer to idle
            elev->set_floor(currentFloor); 
            Serial.println("ELEVATOR " + String(elev->get_number()) + " CURRENTLY ON FLOOR # " + String(toFloor) + "!");

            if(stoppingFloors->contains(currentFloor)){
                Serial.println("ELEVATOR " + String(elev->get_number()) + " CURRENTLY LEAVING AND PICKING PEOPLE ON FLOOR # " + String(toFloor) + "!");
                // elev->set_load_weight(), leave people here
                // elev->set_load_weight(), and pick more people here, figure out how to decide which to do when
                stoppingFloors->remove(currentFloor);
            }
        }
    }
}


bool MovingState::canRun(){
    return run;
}

void MovingState::setRun(bool set){
    run = set;
}

