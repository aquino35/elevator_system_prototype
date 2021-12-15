#include "SystemServer.h"
#include "FSM.h"


SystemServer* server = new SystemServer();
Elevator* elev = new Elevator(1);
FSM* state_machine = new FSM(elev);

void setup(void) 
{
  server->setup();
  state_machine->setup();
}


void loop() 
{
  server->loop();
  state_machine->energy_update();
}