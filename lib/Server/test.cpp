#include "cobs.h" 
#include <stdlib.h>
using namespace std;

int main(){
    uint8_t* num = (uint8_t*)9;
    uint8_t* newNum; 
    cobs_encode(num, sizeof(newNum), newNum);
    return 0;

}