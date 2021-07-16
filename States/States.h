#pragma once

class State{

    public:
        virtual State& getState() = 0; //use dynamic casting to check if an object is of a certain state?
};