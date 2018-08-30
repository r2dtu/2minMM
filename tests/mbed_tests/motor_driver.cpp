#include "mbed.h"
#include "TB6612FNG.h"

#define TB6612FNG_PIN_PWMA  PA_5
#define TB6612FNG_PIN_AIN1  PA_6
#define TB6612FNG_PIN_AIN2  PA_7
#define TB6612FNG_PIN_PWMB  PC_0
#define TB6612FNG_PIN_BIN1  PC_1
#define TB6612FNG_PIN_BIN2  PC_2
#define TB6612FNG_PIN_NSTBY PA_4 // unused

TB6612FNG driver( TB6612FNG_PIN_PWMA, TB6612FNG_PIN_AIN1, TB6612FNG_PIN_AIN2,
                    TB6612FNG_PIN_PWMB, TB6612FNG_PIN_BIN1, TB6612FNG_PIN_BIN2,
                    TB6612FNG_PIN_NSTBY );
float fPwmPeriod;
float fPwmPulsewidth;

int main() {

    fPwmPeriod = 0.00002f;      // 50 kHz
    fPwmPulsewidth = 0.50;      // 50% duty cycle
    driver.setPwmAperiod(fPwmPeriod);
    driver.setPwmBperiod(fPwmPeriod);
    driver.setPwmApulsewidth(fPwmPulsewidth);
    driver.setPwmBpulsewidth(fPwmPulsewidth);

    while (1) {
        driver.motorA_cw();
        wait(1);
        driver.motorA_ccw();
        wait(1);
        driver.motorA_stop();
        wait(1);
        driver.motorB_cw();
        wait(1);
        driver.motorB_ccw();
        wait(1);
        driver.motorB_stop();
        wait(1);
    }
}
