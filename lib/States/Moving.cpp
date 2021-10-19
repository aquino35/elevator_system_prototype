#include "Moving.h"

//MISSING MOVING STATE FUNCTIONALITIES

void Moving::start(Elevator* elev, uint8_t floor){
    elev->set_door_status(false);
    elev->set_light_status(true);

    if(floor == elev->get_floor()){ //transition to idle state somehow
        Serial.println("ELEVATOR " + String(elev->get_number()) + " IS ON THIS SAME FLOOR!");
    }

    else if(floor <= elev->get_max_floor()){ 
        this->toFloor = floor;

        if(currentFloor < this->toFloor){ //direction lock
            DIRECTION = UP;
        }

        else if (currentFloor > this->toFloor){
            DIRECTION = DOWN;
        }

        Serial.println("ELEVATOR " + String(elev->get_number()) + " EN ROUTE TO FLOOR# " + String(toFloor) + "!");
    }

    else{ //transition to idle state somehow
        Serial.println("FLOOR # " + String(floor) + " DOESNT EXIST!");
    }
}

void Moving::moving(Elevator* elev, Set* stoppingFloors){ //Set implemented with Linked List
    uint8_t currentFloor = elev->get_floor();
    this->canRun = false;
    while (currentFloor != this->toFloor) 
    {
        if(DIRECTION == UP){ //direction lock
            currentFloor++;
        }

        else if (DIRECTION == DOWN){
            currentFloor--;
        }
        
        delay(2000000); //2 second delay
        Serial.println("ELEVATOR " + String(elev->get_number()) + " CURRENTLY ON FLOOR # " + String(toFloor) + "!");

        if(stoppingFloors.contains(currentFloor)){
            Serial.println("ELEVATOR " + String(elev->get_number()) + " CURRENTLY LEAVING AND PICKING PEOPLE ON FLOOR # " + String(toFloor) + "!");
            // elev->set_load_weight(), leave people here
            // elev->set_load_weight(), and pick more people here, figure out how to decide which to do when
            stoppingFloors.remove(currentFloor);
        }
    }
    
}


bool Moving::canRun(){
    return canRun;
}

void Moving::setRun(bool set){
    canRun = set;
}

