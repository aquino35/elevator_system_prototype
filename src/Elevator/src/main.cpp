#include "ElevatorSystem/Elevator.h"

String serData;
Elevator* elevator = new Elevator();
State* initialState = new InitialState(elevator, 1, 12, 65);

elevator->setState(initialState);

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to the Elevator System Prototype!");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
      serData = Serial.readString();
      Serial.print("Command executed: ");
      elevator->setDoorState(true);
      Serial.println(elevator->isDoorState());
      delay(5000);

  }
}

int main(){
  return 0;
}