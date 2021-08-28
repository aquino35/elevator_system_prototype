#include <stdint.h>

/* 
 *  This script contains all the methods of the
 *  server object used to process anything given by a Client.
 */ 

#pragma once
#include <Arduino.h>
#include <SerialMessage.h>



class Server {

public:
        // Constructor
        Server(); 

        void begin();
        void run();
        void respond();
        void end(); 
};