#include "ElevatorSystem/Elevator.h"

String serData;
Elevator* elevator = new Elevator(); //elevator obj
State* initialState = new InitialState(elevator, 1, 12, 65);

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
      Serial.println(elevator->isDoorStatus());
      delay(5000);

  }
}

int main(){
  return 0;
}