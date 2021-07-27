#include "Elevator.h"
#include "InitialState.h"
#include "IdleState.h"

String serData;
uint16_t serInt;

Elevator* elevator = new Elevator(); 
InitialState* initialState = new InitialState(elevator, (uint8_t) 1, (uint8_t) 12, (uint8_t) 25);
IdleState* idleState = new IdleState(elevator);

void setup() {
  Serial.begin(9600);
  elevator->setState(initialState);
  Serial.println("Welcome to the Elevator System Prototype!");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    
      serData = Serial.readString();
      Serial.print("Command executed: ");
      elevator->setDoorStatus(true);
      Serial.println((elevator->isDoorStatus()) ? "Door is open." : "Door is closed.");

      //Testing Initial State
      Serial.print("Command executed: ");
      Serial.println("Current elevator State: " + elevator->getState());
      delay(5000);

      //Testing Idle State
      elevator->setState(idleState);
      Serial.print("Command executed: ");
      Serial.println("Current elevator State: " + elevator->getState());
      delay(2000);

      //Testing load
      serData = Serial.readString();
      serInt = (uint16_t) serData.toInt();
      Serial.print("Command executed: ");
      idleState->load(serInt);
      Serial.println("Current elevator Weight: " + elevator->getLoadWeight());
      delay(2000);

      //Testing unloading of elevator
      serData = Serial.readString();
      serInt = (uint16_t) serData.toInt();
      idleState->unload(serInt);
      Serial.print("Command executed: ");
      Serial.println("Current elevator Weight: " + elevator->getLoadWeight());
      delay(5000);
    }
}
