#include <SystemServer.h>
//#include "States/FSM.h"



SystemServer* server = new SystemServer();

void setup(void) 
{
  server->setup();
}


void loop() 
{
  server->loop();
}