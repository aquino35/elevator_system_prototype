#include <Arduino.h>
#include "ElevatorSystem/Elevator.h"
//#include <string.h>

//using std::string;

String serData;
Elevator elevator;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to the Elevator System Prototype!");
  delay(2000);
}

void loop() {
  //elevator = new Elevator();
  if (Serial.available() > 0) {
      serData = Serial.readString();
      Serial.print("Command executed: ");
      elevator.setDoorState(true);
      //mapper(keypad);
      Serial.println(elevator.isDoorState());
      delay(5000);

  }
}