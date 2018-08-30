#include "mbed.h"

#define ADC_IR_RECV1    PA_0
#define ADC_IR_RECV2    PA_1
#define ADC_IR_RECV3    PA_2
#define ADC_IR_RECV4    PA_3

AnalogIn LH_RECV(ADC_IR_RECV1);
AnalogIn LF_RECV(ADC_IR_RECV2);
AnalogIn RF_RECV(ADC_IR_RECV3);
AnalogIn RH_RECV(ADC_IR_RECV4);

DigitalOut led(LED1);

int main() {
    float meas;
    
    printf("\nAnalogIn example\n");
    
    while(1) {
        meas = LH_RECV.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
        meas = meas * 3300; // Change the value to be in the 0 to 3300 range
        printf("measure = %.0f mV\n", meas);
        if (meas > 2000) { // If the value is greater than 2V then switch the LED on
          led = 1;
        }
        else {
          led = 0;
        }
        wait(0.2); // 200 ms
    }
}

