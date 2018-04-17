#include "mbed.h"

#define IR_EMIT1 PC_9
#define IR_EMIT2 PC_10
#define IR_EMIT3 PC_11
#define IR_EMIT4 PC_12

BusOut driver(IR_EMIT1, IR_EMIT2, IR_EMIT3, IR_EMIT4);

int main() {
    
    while(1) {
        driver = 0x1; // 0001
        wait(0.2); // 200 ms
        driver = 0x2; // 0010
        wait(0.2); // 200 ms
        driver = 0x4; // 0100
        wait(0.2); // 200 ms
        driver = 0x8; // 1000
        wait(0.2); // 200 ms
    }
}

