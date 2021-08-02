#include "Elevator.h"
#include "InitialState.h"
#include "IdleState.h"
#include "FSM.cpp"

String serData;
int serInt;

Elevator* elevator = new Elevator(); 
FSM* state_machine = new FSM(); 

IdleState* idleState = new IdleState(elevator);


void setup() {
  Serial.begin(9600);
  state_machine -> setup();
  Serial.println("-- Welcome to the Elevator System Prototype! --");
  delay(2000);
}

void loop() {

  if (Serial.available() > 0) {

    state_machine -> run(elevator);

    serData = Serial.readStringUntil('\n');
    Serial.print("Command executed: ");
    elevator->setDoorStatus(true);
    Serial.println((elevator->isDoorStatus()) ? "Door is open." : "Door is closed.");

    //Testing States
    serData = Serial.readStringUntil('\n');
    Serial.print("Command executed: ");
    Serial.println("Current elevator State: " + elevator->getStateName());

    //Testing load
    serInt = Serial.parseInt();
    serInt = (uint16_t) serInt;
    idleState->load(serInt);
    Serial.print("Current elevator Weight: ");
    Serial.println(elevator->getLoadWeight());
    delay(2000);
  
    //Testing unloading of elevator
    serInt = Serial.parseInt();
    serInt = (uint16_t) serInt;
    idleState->unload(serInt);
    Serial.print("Current elevator Weight: ");
    Serial.println(elevator->getLoadWeight());
    delay(2000);
    }
}