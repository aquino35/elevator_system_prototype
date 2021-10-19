#pragma once
#include <stdint.h>
#include <Arduino.h>

class Set{

    private:


    public:
        uint8_t contains(uint8_t elem);
        uint8_t remove(uint8_t elem);
};