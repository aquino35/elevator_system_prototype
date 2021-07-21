#include "ElevatorSystem/Elevator.h"
//#include "States/InitialState.h"

String serData;
Elevator* elevator = new Elevator(); 
//State* initialState = new InitialState(elevator, (uint8_t) 1, (uint8_t) 12, (uint8_t) 25);

void setup() {
  Serial.begin(9600);
  //elevator->setState(initialState);
  Serial.println("Welcome to the Elevator System Prototype!");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
      serData = Serial.readString();
      Serial.print("Command executed: ");
      elevator->setDoorStatus(true);
      Serial.println(elevator->isDoorStatus());
      delay(5000);
  }
}
