#include "MovingState.h"

/**
* Contructor for the moving state. Initializes with the given elevator as a parameter.
*
* @param elevator The elevator being initialized in the current state.
*/
MovingState::MovingState(Elevator* elevator){
    this->elev = elevator;
    stoppingFloors = elevator->get_stopping_floors();
}

/**
* Activating the moving state allows the elevator to turn the lights on and open the doors,
* allowing the elevator to recieve people. 
*
*/ 
void MovingState::start(){
    elev->close();
    elev->turn_lights_on();
}

/**
* Calculates and returns the nearest requested floor to the elevator's current floor. Iterates over the stopping floors set
* and looks for the one closest to the current floor, in order words, the floor whose difference is the smallest.
*
* @return The floor closest to the elevator's current floor. -1 If no floors were found. 
*/ 
uint8_t MovingState::get_nearest_floor()
{
    if(stoppingFloors->size() < 1){
        return -1; //SWITCH TO IDLE
    }

    uint8_t nearestDifference = 100; //akin to javas Integer.MAX_VALUE  
    uint8_t goToFloor;
    
    for(int i = 0; i < stoppingFloors->size(); i++) //get the nearest floor
    {
        uint8_t currentStopping = stoppingFloors->get(i);

        if(abs(currentStopping - elev->get_floor()) <= nearestDifference && currentStopping != elev->get_floor()){
            nearestDifference = abs(currentStopping - elev->get_floor());
            goToFloor = currentStopping;
        }
    }
    return goToFloor;
}

/**
* Gets the nearest requested floor to the elevator's current floor, and sets a direction based on that. If the 
* nearest floor is less than or equals to the max floor and above the current floor, sets the direction lock
* upwards. Else, sets it downwards. If the nearest floor isn't a positive value, switches back to idle state
* by disabling the state's run attribute. Else, allows the elevator to move.
*
*/ 
void MovingState::set_direction(void)
{
    uint8_t floor = get_nearest_floor();

    if(floor == -1){
        Serial.println("ELEVATOR #" + String(elev->get_number()) + " HAS NO REQUESTED FLOORS!");
        run = false;
        return;
    }


    if(floor <= elev->get_max_floor()){ 
        if(elev->get_floor() < floor){ //direction lock
            directionLock = UP;
        }

        else if (elev->get_floor() > floor){
            directionLock = DOWN;
        }

        Serial.println("ELEVATOR #" + String(elev->get_number()) + " EN ROUTE TO FLOOR #" + String(floor) + "!");
        run = true;
    }

    else{ 
        Serial.println("FLOOR #" + String(floor) + " DOESNT EXIST!");
        run = false;
    }

}

/**
* Sets a two second timer to allow the elevator to transition between floors. 
* 
*/ 
void MovingState::moving_timer(void)
{
    begin = clock();
    timeSpent = (double)(clock() - begin);

    Serial.println( "ELEVATOR #" + String(elev->get_number()) + " TRANSITIONING TO ANOTHER FLOOR!");

    while(true){ //2 second timer
        timeSpent = (double)(clock() - begin);
        if(timeSpent >= 2000.00) return;
    }
}

/**
* Moves the elevator to the nearest floor: the floors either immediately above or below the current floor,
* depending on whether the current floor is the first or the last floor. Used by the emergency state to safely
* transition to the nearest floor and unload people. 
* 
*/ 
void MovingState::move_nearest(void) 
{
    uint8_t currentFloor = elev->get_floor();  
    
    //will be called after emergency state so we don't care about whether we can run it or not
    
    if(currentFloor != elev->get_max_floor()){ //direction to move
        currentFloor++; 
    }

    else{
        currentFloor--;
    }
        
    moving_timer();
    elev->set_floor(currentFloor); 
    Serial.println("ELEVATOR #" + String(elev->get_number()) + " CURRENTLY ON FLOOR #" + String(elev->get_floor()) + "!" );
    
}

/**
* Moves the elevator to the nearest requested floor based on the direction lock and whether the state can run, one floor at a time. 
* If a the the current floor was previously requested, removes the current floor, and lets the Finite State Machine know that a stop
* has been made. Opens the doors and picks up passengers.
*
*/ 
void MovingState::move(void){ 
    uint8_t currentFloor = elev->get_floor();    

    if(run && directionLock != null){ 
        if(directionLock == UP){ 
            currentFloor++;
        }

        else if (directionLock == DOWN){
            currentFloor--;
        }
        
        moving_timer();
        elev->set_floor(currentFloor); 
        Serial.println("ELEVATOR #" + String(elev->get_number()) + " CURRENTLY ON FLOOR #" + String(currentFloor) + "!" );

        if(stoppingFloors->contains(currentFloor)){
            stoppingFloors->remove(currentFloor);
            stopped = true;
            elev->open();
        }
        else stopped = false;
    }
}


/**
* Checks whether the elevator should change its direction lock. If the direction lock is set to go up,
* and there are more requested floors above the current floor, doesn't change the direction lock.
* Likewise, if the direction lock is set downwards and there are more floors below, doesn't change 
* the direction lock. Else, changes the direction lock in the Finite State Machine with a call to set_direction().
*
* @return A boolean indicating whether the elevator's direction lock should change.
*/ 
bool MovingState::should_switch_direction(void) 
{ 
    bool shouldChange = true;

    for(int i = 0; i < stoppingFloors->size(); i++) //get the nearest floor 
    {
        uint8_t otherFloors = stoppingFloors->get(i);

        if(directionLock == UP && otherFloors > elev->get_floor()){ //more floors up
            shouldChange = false;            
        }

        else if(directionLock == DOWN && otherFloors < elev->get_floor()){ //more floors down
            shouldChange = false;            
        }

    }
    return shouldChange;
}

/**
* Checks whether the elevator should keep moving, based on whether there are requested floors or not.

* @return A boolean, denoting whether the elevator should move or not based on the number of requested floors.
*         Stops moving if there are no other requested floors. 
*/ 
bool MovingState::can_move(){
    return elev->get_stopping_floors()->size() != 0;
}

/**
* Signals whether the elevator made a stop or not.
*
* @return A boolean, indicating whether the elevator stopped or not.
*/ 
bool MovingState::made_stop(void){
    return stopped;
}

/**
*  Returns a boolean indicating wether the current state can run. 
*
* @return A boolean, indicating whether the elevator can run or not.
*/ 
bool MovingState::can_run(void){
    return run;
}

/**
*  Receives a boolean and sets the state's current run attribute, denoting whether the state can be run. 
*
* @param set Sets the state's run attribute to the given boolean parameter.
*/ 
void MovingState::set_run(bool set){
    this->run = set;
}

/**
*  Identifies the current state's name. 
*
* @return The current state's name, as a string.
*/ 
String MovingState::current_state()
{
    return this->stateName;
}

/**
*  The state's destructor. The elevator is cleared out in the Finite State Machine.
*/ 
MovingState::~MovingState(){};
