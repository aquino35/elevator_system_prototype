#include "SystemServer.h"
#include "FSM.h"


SystemServer* server = new SystemServer();

Elevator* elevator_1 = new Elevator(0);
Elevator* elevator_2 = new Elevator(1);

FSM* fsm_1 = new FSM(elevator_1);
FSM* fsm_2 = new FSM(elevator_2);


void setup(void) 
{
  server->setup();
  server->communicate();
  fsm_1->setup();
  fsm_2->setup();
}


void loop() 
{
  server->communicate();
  fsm_1->energy_update();
  fsm_2->energy_update();
}