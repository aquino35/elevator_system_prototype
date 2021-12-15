#include "SystemServer.h"
#include "FSM.h"


SystemServer* server = new SystemServer();
Elevator* elev_ard_1 = new Elevator(1);
Elevator* elev_ard_2 = new Elevator(2);

FSM* state_machine_ard_1 = new FSM(elev_ard_1);
FSM* state_machine_ard_2 = new FSM(elev_ard_2);


void setup(void) 
{
  server->setup();
  state_machine_ard_1->setup();
  state_machine_ard_2->setup();
}


void loop() 
{
  server->loop();
  state_machine_ard_1->energy_update();
  state_machine_ard_2->energy_update();

}