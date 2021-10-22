#include "Moving.h"

//MISSING MOVING STATE FUNCTIONALITIES

void Moving::start(Elevator* elev, uint8_t floor){
    elev->set_door_status(false);
    elev->set_light_status(true);

    if(floor == elev->get_floor()){ //transition to idle state somehow
        Serial.println("ELEVATOR " + String(elev->get_number()) + " IS ON THIS SAME FLOOR!");
        canRun = false;
        return;
    }

    else if(floor <= elev->get_max_floor()){ 
        this->toFloor = floor;

        if(currentFloor < this->toFloor){ //direction lock
            direction = UP;
        }

        else if (currentFloor > this->toFloor){
            direction = DOWN;
        }

        Serial.println("ELEVATOR " + String(elev->get_number()) + " EN ROUTE TO FLOOR# " + String(toFloor) + "!");
    }

    else{ //transition to idle state somehow
        Serial.println("FLOOR # " + String(floor) + " DOESNT EXIST!");
        canRun = false;
        return;
    }
}

void Moving::moving(Elevator* elev, Set* stoppingFloors){ //Set implemented with Linked List
    uint8_t currentFloor = elev->get_floor();

    if(canRun){
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


bool Moving::canRun(){
    return canRun;
}

void Moving::setRun(bool set){
    canRun = set;
}

