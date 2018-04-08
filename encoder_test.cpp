#include "mbed.h"
#include "encoder.h"

Encoder motor1(PC_4,PC_5,true);
InterruptIn 
Serial pc(USBTX,USBRX);
DigitalOut pc6(PC_6);
DigitalOut pc7(PC_7);

int main () {
    pc.baud(115200);
    pc6 = 0; 
    pc7 = 1;
    while(1) {
        wait(1);
        pc6 = !pc6;
        pc7 = !pc7;
        pc.printf("pos: %d, speed %f \r\n",motor1.getPosition(), motor1.getSpeed());
    }
}